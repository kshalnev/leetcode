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
    reverse_words_in_str.cpp \
    palindrome_partitioning.cpp \
    bst_find_rev_kth_3.cpp \
    bst_find_rev_kth_1.cpp \
    bst_find_rev_kth_2.cpp

HEADERS += \
    std.hpp \
