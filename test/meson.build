gmock = dependency('gmock')
gtest = dependency('gtest')

# sentry.hpp
sentry_test_sources = [
    'sentry_test.cpp'
]
sentry_test_dependencies = [
    libtide_dep,
    gmock,
    gtest
]
sentry_test = executable(
    'sentry',
    sentry_test_sources,
    dependencies : sentry_test_dependencies
)
test('sentry.hpp', sentry_test)


# trace.hpp
trace_test_sources = [
    'trace_test.cpp'
]
trace_test_dependencies = [
    libtide_dep,
    gmock,
    gtest
]
trace_test = executable(
    'trace',
    trace_test_sources,
    dependencies : trace_test_dependencies
)
test('trace.hpp', trace_test)

# trace.hpp - custom prefix
trace_prefix_test_sources = [
    'trace_prefix_test.cpp'
]
trace_prefix_test_dependencies = [
    libtide_dep,
    gmock,
    gtest
]
trace_prefix_test = executable(
    'trace_prefix',
    trace_prefix_test_sources,
    dependencies : trace_prefix_test_dependencies
)
test('trace.hpp - custom prefix', trace_prefix_test)

# trace.hpp - custom ostream
trace_ostream_test_sources = [
    'trace_ostream_test.cpp'
]
trace_ostream_test_dependencies = [
    libtide_dep,
    gmock,
    gtest
]
trace_ostream_test = executable(
    'trace_ostream',
    trace_ostream_test_sources,
    dependencies : trace_ostream_test_dependencies
)
test('trace.hpp - custom ostream', trace_ostream_test)
