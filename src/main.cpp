/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#include <iostream>
#include <json/json.h>
#include <fstream>
#include "cxxopts.hpp"
#include "VERSION.h"
#include "enquirer.hpp"

using namespace std;
using namespace enquirer;

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
            ("g,generate", "Generate a new config file", cxxopts::value<string>()->implicit_value("config.json"));
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

    if (result.count("generate")) {
        string config = result["generate"].as<string>();
        // TODO : generate a new config file using Enquirer
        return 0;
    }

    if (!result.count("config")) {
        cout << color::bold << color::red << "You must specify a config file" << color::reset << endl << endl;
        cout << options.help() << endl;
        return 1;
    }
    string config_file = result["config"].as<string>();
    ifstream config(config_file);
    if (!config.is_open()) {
        cout << color::bold << color::red << "Unable to open config file" << color::reset << endl << endl;
        return 1;
    }
    Json::Value root;
    config >> root;

    string input = result.count("input") ? result["input"].as<string>() : "";
    string output = result.count("output") ? result["output"].as<string>() : "";

    // TODO : Run algorithms using config file

    return 0;
}
