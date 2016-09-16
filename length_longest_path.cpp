#include "std.hpp"

// https://leetcode.com/problems/longest-absolute-file-path/

class Solution1 {
public:
    struct Node {
        string name;
        size_t distance = 0;
        Node* parent = nullptr;
        vector<unique_ptr<Node>> children;
        bool is_file = false;
        int level = -1;
        Node* addChild(string name) {
            children.emplace_back(new Node());
            Node* node = children.back().get();
            node->name = move(name);
            node->is_file = node->name.find('.') != string::npos;
            if (!node->is_file) node->name += '/';
            node->distance = distance + node->name.length();
            node->parent = this;
            node->level = level + 1;
            return node;
        }
    };

    template <typename Fn>
    static void readLines(const string& input, Fn&& fn)
    {
        size_t p = 0;
        while (true)
        {
            const size_t d = input.find('\n', p);
            if (d == string::npos) {
                fn(string(input.begin() + p, input.end()));
                return;
            }
            fn(string(input.begin() + p, input.begin() + d));
            p = d + 1;
        }
    }

    static int getLevel(const string& name)
    {
        int level = 0;
        for (auto i = name.begin();i != name.end(); ++i) {
            if (*i != '\t')
                break;
            ++level;
        }
        return level;
    }

    int lengthLongestPath(string input) {
        Node root;
        Node* parent = &root;
        Node* longest = &root;
        readLines(input, [&](string&& s) {
            const int level = getLevel(s);
            while (level < (1 + parent->level))
                parent = parent->parent;
            auto child = parent->addChild(string(s.begin() + level, s.end()));
            if (child->is_file && child->distance >= longest->distance)
                longest = child;
            if (!child->is_file)
                parent = child;
        });
        return longest->distance;
    }
};

class Solution2 {
public:
    struct Folder {
        size_t distance;
        size_t level;
    };

    template <typename Fn>
    static void readLines(const string& input, Fn&& fn) {
        for (size_t p = 0;;) {
            const size_t d = input.find('\n', p);
            if (d == string::npos) {
                fn(string(input.begin() + p, input.end()));
                break;
            }
            fn(string(input.begin() + p, input.begin() + d));
            p = d + 1;
        }
    }

    static string normalizeTabs(const string& s, size_t max_level) {
        size_t spaces = 0;
        for (auto i = s.begin();
             i != s.end() && *i == ' ';
             ++i, ++spaces) {}
        size_t tabs = min(max_level, spaces / 4);
        if (tabs == 0) return s;
        string t(tabs, '\t');
        return t + string(s.begin() + tabs * 4, s.end());
    }

    static size_t getLevel(const string& s) {
        size_t level = 0;
        for (auto i = s.begin();
             i != s.end() && *i == '\t';
             ++i, ++level) {}
        return level;
    }

    static bool isFile(const string & name) {
        return name.find('.') != string::npos;
    }

    int lengthLongestPath(string input) {
        size_t res = 0;
        stack<Folder> folders;
        readLines(input, [&](string&& s) {
            const size_t max_level = folders.empty() ? 0 : folders.top().level + 1;
            s = normalizeTabs(s, max_level);
            const size_t level = getLevel(s);
            if (level != 0) {
                s = string(s.begin() + level, s.end());
            }
            while (!folders.empty() && folders.top().level >= level)
                folders.pop();
            const size_t parent_distance = folders.empty() ? 0 : folders.top().distance;
            const size_t current_distance = parent_distance + s.length();
            if (isFile(s)) {
                if (current_distance > res)
                    res = current_distance;
            } else {
                folders.push(Folder{current_distance + 1, level});
            }
        });
        return static_cast<int>(res);
    }
};

void test_lengthLongestPath()
{
    using Solution = Solution2;

    assert(10 == Solution().lengthLongestPath(
        "a\n"
        "\tb\n"
        "\t\tc.txt\n"
        "\taaaa.txt"));

    assert(12 == Solution().lengthLongestPath("dir\n    file.txt"));
    assert(16 == Solution().lengthLongestPath("dir\n        file.txt"));
    assert(12 == Solution().lengthLongestPath("dir\n\tfile.txt"));
    assert(32 == Solution().lengthLongestPath(
        "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"));
    assert(20 == Solution().lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"));

    const char * s =
    "sladjf\n"
    "\tlkjlkv\n"
    "\t\tlkjlakjlert\n"
    "\t\t\tlaskjglaksjf\n"
    "\t\t\t\tlakjgfljrtlj\n"
    "\t\t\t\t\tlskajflakjsvlj\n"
    "\t\t\t\t\t\tlskgjflkjrtlrjt\n"
    "\t\t\t\t\t\t\tlkjglkjlvkjdlvkj\n"
    "\t\t\t\t\t\t\t\tlfjkglkjfljdlv\n"
    "\t\t\t\t\t\t\t\t\tlkdfjglerjtkrjkljsd.lkvjlkajlfk\n"
    "\t\t\t\t\t\t\tlskfjlksjljslvjxjlvkzjljajoiwjejlskjslfj.slkjflskjldfkjoietruioskljfkljf\n"
    "\t\t\t\t\tlkasjfljsaljlxkcjzljvl.asljlksaj\n"
    "\t\t\t\tasldjflksajf\n"
    "\t\t\t\talskjflkasjlvkja\n"
    "\t\t\t\twioeuoiwutrljsgfjlskfg\n"
    "\t\t\t\taslkjvlksjvlkjsflgj\n"
    "\t\t\t\t\tlkvnlksfgk.salfkjaslfjskljfv\n"
    "\t\t\tlksdjflsajlkfj\n"
    "\t\t\tlasjflaskjlk\n"
    "\t\tlsakjflkasjfkljas\n"
    "\t\tlskjvljvlkjlsjfkgljfg\n"
    "\tsaljkglksajvlkjvkljlkjvksdj\n"
    "\tlsakjglksajkvjlkjdklvj\n"
    "\tlskjflksjglkdjbkljdbkjslkj\n"
    "\t\tlkjglkfjkljsdflj\n"
    "\t\t\tlskjfglkjdfgkljsdflj\n"
    "\t\t\t\tlkfjglksdjlkjbsdlkjbk\n"
    "\t\t\t\t\tlkfgjlejrtljkljsdflgjl\n"
    "\t\t\t\t\tsalgkfjlksfjgkljsgfjl\n"
    "\t\t\t\t\tsalkflajwoieu\n"
    "\t\t\t\t\t\tlaskjfglsjfgljkkvjsdlkjbklds"
    "\n\t\t\t\t\t\t\tlasjglriotuojgkjsldfgjsklfgjl\n"
    "\t\t\t\t\t\t\t\tlkajglkjskljsdljblkdfjblfjlbjs\n"
    "\t\t\t\t\t\t\t\t\tlkajgljroituksfglkjslkjgoi\n"
    "\t\t\t\t\t\t\t\t\t\tlkjglkjkljkljdkbljsdfljgklfdj\n"
    "\t\t\t\t\t\t\t\t\t\t\tlkjlgkjljgslkdkldjblkj\n"
    "\t\t\t\t\t\t\t\t\t\t\t\tlkjfglkjlkjbsdklj.slgfjalksjglkfjglf\n"
    "\t\t\t\t\t\t\t\t\t\t\t\tlkasjrlkjwlrjljsl\n"
    "\t\t\t\t\t\t\t\t\t\t\t\t\tlksjgflkjfklgjljbljls\n"
    "\t\t\t\t\t\t\t\t\t\t\t\t\t\tlkjsglkjlkjfkljdklbjkldf\n"
    "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tlkjglkjdlsfjdglsdjgjlxljjlrjsgjsjlk\n"
    "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tlkjsgkllksjfgjljdslfkjlkasjdflkjxcljvlkjsgkljsfg\n"
    "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tlaskjlkjsakljglsdjfgksdjlkgjdlskjb\n"
    "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tlkajsgfljfklgjlkdjgfklsdjklj\n"
    "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tlkjfglkjlkgjlkjl.aslkjflasjlajglkjaf\n"
    "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tlkjasflgjlskjglkfjgklgsdjflkbjsdklfjskldfjgklsfdjgklfdjgl\n"
    "\tlskadjlkjsldwwwwwfj\n"
    "\t\tlkjflkasjlfjlkjajslfkjlasjkdlfjlaskjalvwwwwwwwwwwwwwwwkjlsjfglkjalsjgflkjaljlkdsjslbjsljksldjlsjdlkjljvblkjlkajfljgasljfkajgfljfjgldjblkjsdljgsldjg.skljf";
    assert(528 == Solution().lengthLongestPath(s));
}
