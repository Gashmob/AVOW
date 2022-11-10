/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#include <iostream>
#include "cxxopts.hpp"
#include "VERSION.h"
#include "algorithms.hpp"
#include "Image.hpp"

using namespace std;

int main(int argc, char **argv) {
    cxxopts::Options options("avow", "Another View Of World\nVersion: " + VERSION_STRING + "\nLicense: " + LICENSE);
    options.custom_help("[options...]");
    options.positional_help("<image input>");
    options.add_options("General")
            ("h,help", "Print help")
            ("v,version", "Print version")
            ("i,input", "Input image", cxxopts::value<string>())
            ("o,output", "Output image (png,jpg,jpeg,bmp,tga,hdr)", cxxopts::value<string>());
    options.parse_positional({"input", "output"});

    auto adder = options.add_options("Algorithms");
    for (const auto &algorithm: algorithms) {
        algorithm.getOption(&adder);
    }

    // ====================

    cxxopts::ParseResult result;
    try {
        result = options.parse(argc, argv);
    } catch (exception &e) {
        cout << "\033[1;31mSomething went wrong during parsing options\033[00m" << endl << endl;
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

    if (result.count("help") || !result.count("input")) {
        cout << options.help() << endl;
        return 0;
    }

    const std::string input = result["input"].as<string>();
    const std::string output = result.count("output") ? result["output"].as<string>() : input + "_out.png";

    // ====================

    // Open image
    Image *image = nullptr;
    try {
        image = new Image(input);
    } catch (runtime_error &e) {
        cout << "\033[1;31m" << e.what() << "\033[00m" << endl;
        return 1;
    }

    // TODO : run algorithms

    // Save image
    try {
        image->save(output);
        delete image;
    } catch (runtime_error &e) {
        cout << "\033[1;31m" << e.what() << "\033[00m" << endl;
        delete image;
        return 1;
    }

    return 0;
}
