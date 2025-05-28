#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "parsing.hpp"

TSParser *_the_ash_parser = nullptr;

std::string read_file(path file) {
    std::stringstream source_buffer;
    try {
        std::ifstream file_reader(file);

        if (!(source_buffer << file_reader.rdbuf())) {
            throw std::runtime_error("Could not read file " + file.string());
        }
    } catch (const std::exception &exc) {
        throw std::runtime_error("Could not read file " + file.string() + " (" +
                                 exc.what() + ")");
    }

    return source_buffer.str();
}

TSParser *create_parser(const TSLanguage *language) {
    TSParser *parser = ts_parser_new();
    if (!parser) {
        throw std::runtime_error("Could not create new ts parser");
    }
    if (!ts_parser_set_language(parser, language)) {
        uint32_t lang_v = ts_language_abi_version(language);
        uint32_t min_v = TREE_SITTER_MIN_COMPATIBLE_LANGUAGE_VERSION;
        uint32_t max_v = TREE_SITTER_LANGUAGE_VERSION;
        std::clog << "incompatible " << ts_language_name(language)
                  << " parser: " << min_v << " <= " << lang_v
                  << " <= " << max_v;
        ts_parser_delete(parser);
        throw std::runtime_error("Incompatible parser and language versions");
    }

    if (!parser) {
        throw std::runtime_error("Assigning language to ts parser failed");
    }

    return parser;
}

TSParser *get_ash_parser() {
    if (_the_ash_parser == nullptr)
        _the_ash_parser = create_parser(tree_sitter_ash());
    return _the_ash_parser;
}

TSTree *fget_asht(path file) {
    return get_asht(read_file(file));
}

TSTree *get_asht(std::string str) {
    TSParser *parser = get_ash_parser();
    TSTree *tree =
        ts_parser_parse_string(parser, NULL, str.c_str(), str.size());

    if (!tree) {
        throw std::runtime_error("Tree sitter could not parse source file");
    }

    return tree;
}

void on_finished_parsing() {
    if (_the_ash_parser != nullptr)
        ts_parser_delete(_the_ash_parser);
}
