project('pcg', 'c')

cc = meson.get_compiler('c')

include = [
  include_directories('.'),
  include_directories('source'),
]

source_files = [
  'source/pcg.c',
  'examples/basic.c',
]

# change this to false if you do not want to have 32x2 generators
build_32x2 = true

if not build_32x2
  add_global_arguments('-DPCG_NO_32X2', language : 'c')
endif

# change this to false if you do not want to have 64 bit generators
build_64bit = true

if not build_64bit
  add_global_arguments('-DPCG_NO_128BIT', language : 'c')
endif

basic_binary = executable (
  'basic',
  source_files,
  include_directories : include,
)

pcg32_demo_files = [
  'source/pcg.c',
  'examples/pcg32-demo.c',
]

pcg32_binary = executable (
  'pcg32-demo',
  pcg32_demo_files,
  include_directories : include,
)

pcg32_global_demo_files = [
  'source/pcg.c',
  'examples/pcg32-global-demo.c',
]

pcg32_global_binary = executable (
  'pcg32-global-demo',
  pcg32_global_demo_files,
  include_directories : include,
)


if build_32x2
pcg32x2_demo_files = [
  'source/pcg.c',
  'examples/pcg32x2-demo.c',
]

pcg32x2_binary = executable (
  'pcg32x2-demo',
  pcg32x2_demo_files,
  include_directories : include,
)

pcg32x2_global_demo_files = [
  'source/pcg.c',
  'examples/pcg32x2-global-demo.c',
]

pcg32x2_global_binary = executable (
  'pcg32x2-global-demo',
  pcg32x2_global_demo_files,
  include_directories : include,
)
endif  # end 32x2 demos


if cc.has_type('__uint128_t') and build_64bit
pcg64_demo_files = [
  'source/pcg.c',
  'examples/pcg64-demo.c',
]

pcg64_binary = executable (
  'pcg64-demo',
  pcg64_demo_files,
  include_directories : include,
)

pcg64_global_demo_files = [
  'source/pcg.c',
  'examples/pcg64-global-demo.c',
]

pcg64_global_binary = executable (
  'pcg64-global-demo',
  pcg64_global_demo_files,
  include_directories : include,
)
endif  # end 64bit demos
