project('ash', ['cpp', 'c'], default_options: ['cpp_std=c++17'], version: '0.1')

# include directory
inc = include_directories('include')

# dependencies
treesitter = [dependency('tree-sitter'),
     dependency('tree-sitter-ash')]

# Libraries
# Formatting
string = library('string', 'src/string.cpp', include_directories: inc)
colors = library('colors', 'src/tcolor.cpp', include_directories: inc)

# Tree-Sitter stuff
tsparsing = library('tsparsing', 'src/tsparsing.cpp', include_directories: inc, dependencies: treesitter, link_with: colors)
ts2ast = library('ts2ast', [
'src/ts2ast/file.cpp', 'src/ts2ast/definitions.cpp', 'src/ts2ast/common_ast.cpp', 'src/ts2ast/fields.cpp'
], include_directories: inc, dependencies: treesitter, link_with: [colors, tsparsing])

# AST
ast_passes = library('ast_passes', 'src/ast_passes/merge_regexes.cpp', include_directories: inc, link_with: colors)

# NFA
nfa = library('nfa', 'src/nfa/nfa.cpp', include_directories: inc)
nfa_passes_src = files(
  'src/nfa/passes/abstract_pass.cpp',
  'src/nfa/passes/print_nfa.cpp',
  'src/nfa/passes/is_deterministic.cpp'
)
nfa_passes = library('nfa_passes', nfa_passes_src, include_directories: inc, link_with: [nfa, string])

#M Management
pass_manager = library('pass_manager', 'src/pass_manager.cpp', include_directories: inc, dependencies: treesitter, link_with: [nfa, nfa_passes, ts2ast, tsparsing, ast_passes])


# compiler executable
executable(meson.project_name(), '.'.join(meson.project_name(), 'cpp'), include_directories: inc, cpp_args: '-DPROGRAM_VERSION="@0@"'.format(meson.project_version()), dependencies: treesitter, link_with: [tsparsing, colors, pass_manager])
