#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Node {
public:
    vector<Node*> children;
    char letter;
    bool is_end = false;

    Node(char c = '\0') : letter(c), is_end(false) {}
};

int getDepth(Node* node) {
    if (node->children.empty()) return 0;
    int maxDepth = 0;
    for (Node* child : node->children) {
        maxDepth = max(maxDepth, 1 + getDepth(child));
    }
    return maxDepth;
}

void sortChildren(Node* node) {
    sort(node->children.begin(), node->children.end(),
         [](Node* a, Node* b) {
             int depthA = getDepth(a);
             int depthB = getDepth(b);
             if (depthA != depthB) return depthA < depthB;
             return a->letter < b->letter;
         });

    for (Node* child : node->children) {
        sortChildren(child);
    }
}

void collectUrls(Node* node, string path, vector<string>& urls) {
    if (node->is_end) {
        urls.push_back(path);
    }

    for (Node* child : node->children) {
        collectUrls(child, path + child->letter, urls);
    }
}

int countBackspaces(const string& from, const string& to) {
    int common = 0;
    int minLen = min(from.length(), to.length());
    for (int i = 0; i < minLen; i++) {
        if (from[i] == to[i]) common++;
        else break;
    }
    return from.length() - common;
}

int main() {
    int n;
    cin >> n;
    vector<string> inputUrls(n);
    for (int i = 0; i < n; i++) {
        cin >> inputUrls[i];
    }

    Node* root = new Node();

    for (int i = 0; i < n; i++) {
        string url = inputUrls[i];
        Node* curr = root;

        for(size_t j = 0; j < url.length(); j++) {
            char c = url[j];

            Node* found = nullptr;
            for (Node* child : curr->children) {
                if (child->letter == c) {
                    found = child;
                    break;
                }
            }

            if (found == nullptr) {
                Node* child = new Node(c);
                curr->children.push_back(child);
                curr = child;
            } else {
                curr = found;
            }
        }
        curr->is_end = true;
    }

    sortChildren(root);

    vector<string> urls;
    collectUrls(root, "", urls);

    string result = "";
    string lastVisitedUrl = "";
    string current = "";

    for (const string& url : urls) {
        if (!lastVisitedUrl.empty() && current.length() < url.length()) {
            bool canUseTab = true;
            for (size_t i = 0; i < current.length(); i++) {
                if (i >= lastVisitedUrl.length() || current[i] != lastVisitedUrl[i]) {
                    canUseTab = false;
                    break;
                }
            }

            if (canUseTab) {
                result += 'T';
                current = lastVisitedUrl;
            }
        }

        int backspaces = countBackspaces(current, url);
        for (int i = 0; i < backspaces; i++) {
            result += 'B';
            current.pop_back();
        }

        for (size_t i = current.length(); i < url.length(); i++) {
            result += url[i];
            current += url[i];
        }

        result += 'E';

        lastVisitedUrl = url;
        current = "";
    }

    cout << result.length() << endl;
    cout << result << endl;

    return 0;
}