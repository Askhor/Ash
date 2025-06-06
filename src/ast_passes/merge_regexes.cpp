#include <sstream>
#include <stdexcept>

#include "ast/passes/merge_regexes.hpp"

using namespace std;
using namespace ast;

void mr_file(sptr<File> file) {
    for (sptr<Definition> def : file->definitions) {
        merge_regexes(def);
    }
}

sptr<RegexField> create_re_field(string value) {
    sptr<RegexField> field = MKSH(RegexField)();
    sptr<Regex> re = MKSH(Regex)();
    re->value = value;
    field->regex = re;
    return field;
}

void collapse_re(stringstream &regex, int &regex_length,
                 vector<sptr<Field>> &fields) {
    if (regex_length > 0) {
        fields.emplace_back(create_re_field(regex.str()));

        regex.clear();
        regex.str("");
        regex_length = 0;
    }
}

void mr_node(sptr<NodeDefinition> node) {
    vector<sptr<Field>> &old_fields = node->fields;
    vector<sptr<Field>> new_fields;

    unsigned long i = 0;
    stringstream regex;
    int regex_length = 0;

    for (; i < old_fields.size(); i++) {

        if (old_fields[i]->get_type() == ast::Type::REGEX_FIELD) {

            sptr<RegexField> field = CAST(RegexField)(old_fields[i]);
            string value = field->regex->value;
            regex << value;
            regex_length += value.size();

        } else {
            collapse_re(regex, regex_length, new_fields);
            new_fields.emplace_back(old_fields[i]);
        }
    }

    collapse_re(regex, regex_length, new_fields);

    node->fields.swap(new_fields);
}

void ast::merge_regexes(sptr<Node> node) {
    switch (node->get_type()) {
    case Type::FILE:
        mr_file(CAST(File)(node));
        return;
    case Type::TOKEN:
    case Type::ABSTRACT_NODE:
        return;
    case Type::NODE:
        mr_node(CAST(NodeDefinition)(node));
        return;
    default:
        throw runtime_error("Merge Regexes cannot be called on nodes of type " +
                            node->type_name());
    }
}
