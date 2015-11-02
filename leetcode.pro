TARGET = leetcode

CONFIG += console
CONFIG -= app_bundle
CONFIG += warn_on c++11

TEMPLATE = app

SOURCES += \
    subsets_with_dup.cpp \
    word_pattern.cpp \
    zigzag_level_order.cpp \
    main.cpp \
    combination_sum_2.cpp \
    serialize_deserialize_bst.cpp \
    serialize_deserialize_bt.cpp \
    find_median_from_data_strm.cpp \
    reverse_words_in_str.cpp

HEADERS += \
    std.hpp \
