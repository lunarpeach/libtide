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
