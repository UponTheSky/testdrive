# Compiler flags as a library target
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
## no -Wall; effective cmake(https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)
target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wextra;-Wshadow;-Wformat=2;-Wunused;-Wno-deprecated;-fcolor-diagnostics;-fansi-escape-codes;-g>>"
)
