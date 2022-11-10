/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#include <iostream>
#include <algorithm>
#include "cxxopts.hpp"
#include "VERSION.h"
#include "algorithms.hpp"
#include "Image.hpp"

using namespace std;
using namespace tools;

int main(int argc, char **argv) {
    cxxopts::Options options("avow", "Another View Of World\nVersion: " + VERSION_STRING + "\nLicense: " + LICENSE);
    options.custom_help("[options...]");
    options.add_options("General")
            ("h,help", "Print help")
            ("v,version", "Print version")
            ("i,input", "Input image", cxxopts::value<string>())
            ("o,output", "Output image (png,jpg,jpeg,bmp,tga,hdr)", cxxopts::value<string>());
    auto ignore_opt = {"help", "version", "input", "output"};

    auto adder = options.add_options("Algorithms");
    for (const auto &algorithm: algorithms) {
        algorithm.second->getOption(&adder);
    }

    // ====================

    cxxopts::ParseResult result;
    try {
        result = options.parse(argc, argv);
    } catch (exception &e) {
        cout << bold << red << "Something went wrong during parsing options" << reset << endl << endl;
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

    const std::string input = result.count("input") ? result["input"].as<string>() : "";
    const std::string output = result.count("output") ? result["output"].as<string>() : input + "_out.png";

    // ====================

    // Open image if input
    Image *image = nullptr;
    if (!input.empty()) {
        try {
            image = new Image(input);
        } catch (runtime_error &e) {
            cout << red << e.what() << reset << endl;
            return 1;
        }
    }

    // Get list of algorithms to run
    std::vector<cxxopts::KeyValue> algos;
    for (const auto &res: result) {
        if (find(ignore_opt.begin(), ignore_opt.end(), res.key()) == ignore_opt.end()) // If is not a general opt
            algos.push_back(res);
    }

    // Run algorithms
    if (algos.empty()) {
        cout << magenta << "No algorithm to run" << reset << endl;
    } else {
        for (const auto &algo: algos) {
            auto opt = algo.key();
            if (algorithms.find(opt) != algorithms.end()) {
                auto a = algorithms.at(opt);
                image = a->run(image, split(algo.value()));
            } else {
                cout << bold << red << "Algorithm " + opt + " not found" << reset << endl;
            }
        }
    }

    // Save image
    if (image) {
        try {
            image->save(output);
            delete image;
        } catch (runtime_error &e) {
            cout << bold << red << e.what() << reset << endl;
            delete image;
            return 1;
        }
    }

    return 0;
}
