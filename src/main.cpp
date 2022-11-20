/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#include <iostream>
#include <json/json.h>
#include "cxxopts.hpp"
#include "VERSION.h"
#include "enquirer.hpp"
#include "algorithms.hpp"
#include "tools.hpp"

using namespace std;
using namespace enquirer;

void generate_config(const string &file);

int run_config(const string &file, const string &input, const string &output);

int main(int argc, char **argv) {
    cxxopts::Options options("avow", "Another View Of World\nVersion: " + VERSION_STRING + "\nLicense: " + LICENSE);
    options.custom_help("[options...]");
    options.positional_help("<config>");
    options.add_options()
            ("h,help", "Print help")
            ("v,version", "Print version")
            ("c,config", "Config file", cxxopts::value<string>())
            ("i,input", "Input image", cxxopts::value<string>())
            ("o,output", "Output image (png,jpg,jpeg,bmp,tga,hdr)", cxxopts::value<string>())
            ("g,generate", "Generate a new config file", cxxopts::value<string>()->implicit_value("config.json"))
            ("l,list", "List all available algorithms");
    options.parse_positional({"config"});

    // ====================

    cxxopts::ParseResult result;
    try {
        result = options.parse(argc, argv);
    } catch (exception &e) {
        cout << color::bold << color::red << "Something went wrong during parsing options" << color::reset << endl
             << endl;
        cout << options.help() << endl;
        return 1;
    }

    // ====================

    if (result.count("version")) {
        cout << "    ___ _    ______ _       __\n"
                "   /   | |  / / __ \\ |     / /\n"
                "  / /| | | / / / / / | /| / / \n"
                " / ___ | |/ / /_/ /| |/ |/ /  \n"
                "/_/  |_|___/\\____/ |__/|__/   \n"
                "                              " << endl;
        cout << "avow version " << VERSION_STRING << " - " << VERSION << endl;
        cout << "License: " << LICENSE << endl;
        return 0;
    }

    if (result.count("help") || result.arguments().empty()) {
        cout << options.help() << endl;
        return 0;
    }

    if (result.count("list")) {
        cout << "Available algorithms:" << endl;
        for (auto &algorithm: algorithms) {
            cout << " - " << algorithm.first << endl;
        }
        return 0;
    }

    if (result.count("generate")) {
        string config = result["generate"].as<string>();
        generate_config(config);
        return 0;
    }

    if (!result.count("config")) {
        cout << color::bold << color::red << "You must specify a config file" << color::reset << endl << endl;
        cout << options.help() << endl;
        return 1;
    }
    string config_file = result["config"].as<string>();
    if (!tools::fileExists(config_file)) {
        cout << color::bold << color::red << "Unable to open config file" << color::reset << endl << endl;
        return 1;
    }

    string input = result.count("input") ? result["input"].as<string>() : "";
    string output = result.count("output") ? result["output"].as<string>() : "";

    return run_config(config_file, input, output);
}

void generate_config(const string &file) {
    cout << color::bold << color::magenta << "Let's build a new config file" << color::reset << endl << endl;

    bool input = confirm("Did you need an input image?", true);

    vector<Json::Value> configs;
    vector<string> names;
    vector<string> algo_names = tools::keys(algorithms);
    do {
        string algo = select("Which algorithm do you want to use?", algo_names);
        configs.emplace_back(algorithms[algo]()->config());
        names.emplace_back(algo);
    } while (confirm("Add another algorithm?", false));

    bool output = confirm("Did you have an output image?", true);

    Json::Value root;
    root["input"] = input;
    root["output"] = output;
    for (int i = 0; i < configs.size(); i++) {
        root["configs"][i] = configs[i];
        root["algorithms"][i] = names[i];
    }

    ofstream config(file);
    config << root;
    config.close();

    cout << endl
         << color::green << "Config file " << color::bold << file << color::reset
         << color::green << " generated" << color::reset << endl;
}

int run_config(const string &config_file, const string &input, const string &output) {
    Json::Value config;
    ifstream file(config_file);
    file >> config;
    file.close();

    // Generate input
    Image *img = nullptr;
    if (config.get("input", !input.empty()).asBool()) {
        if (input.empty()) {
            cout << color::bold << color::red << "You must specify an input image" << color::reset << endl;
            return 1;
        }

        cout << color::bold << color::cyan << "Loading input image" << color::reset << endl;
        img = new Image(input);
    }

    for (int i = 0; i < config["configs"].size(); i++) {
        string algo = config["algorithms"][i].asString();
        Json::Value algo_config = config["configs"][i];

        cout << color::bold << color::grey << "Running algorithm " << color::white << algo << color::reset << endl;

        Algorithm *a = algorithms[algo]();
        img = a->run(img, algo_config);
        delete a;
    }

    // Generate output
    if (config.get("output", !output.empty()).asBool()) {
        if (output.empty()) {
            cout << color::bold << color::red << "You must specify an output image" << color::reset << endl;
            return 1;
        }
        if (!img) {
            cout << color::bold << color::red << "Error : Image is null" << color::reset << endl;
            return 1;
        }

        cout << color::bold << color::cyan << "Saving output image" << color::reset << endl;
        img->save(output);
    }

    delete img;

    return 0;
}
