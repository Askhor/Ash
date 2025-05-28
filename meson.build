project('ash', ['cpp', 'c'], default_options: ['cpp_std=c++17'], version: '0.1')

# include directory
inc = include_directories('include')

# dependencies
treesitter = [dependency('tree-sitter'),
     dependency('tree-sitter-ash')]

# libraries
parsing = library('parsing', 'src/parsing.cpp', include_directories: inc, dependencies: treesitter)

# compiler executable
executable(meson.project_name(), '.'.join(meson.project_name(), 'cpp'), include_directories: inc, cpp_args: '-DPROGRAM_VERSION="@0@"'.format(meson.project_version()), link_with: parsing, dependencies: treesitter)
