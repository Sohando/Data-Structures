#include<bits/stdc++.h>
using namespace std;

#define ALPHABET 26
struct Trie {
    Trie* children[ALPHABET];
    bool isEndofWords;
   	Trie() {
        for(int i = 0; i < ALPHABET; ++i) {
            this->children[i] = NULL;
        }
    }
};
void solve() {
    int n, q;
    cin >> n;
    vector<string> keys(n);
    for (auto& it : keys) {
        cin >> it;
    }
    auto newNode = [&]() {
     	Trie* temp = new Trie();
     	return temp;	
    };
    Trie* root = newNode();
    auto build = [&]() {
    	auto insert = [&](Trie* root, string key) {
    	  	Trie* Crawl = root;
			for (int i = 0; i < (int) key.length(); ++i) {
			 	int index = key[i] - 'a';
			 	if (!Crawl->children[index]) {
			 	 	Crawl->children[index] = newNode();
			 	}
			 	Crawl = Crawl->children[index];
			}
			Crawl->isEndofWords = true;
    	};
    	for (auto it : keys) {
			insert(root, it);
    	} 	
    };
    function<void(Trie* root, char*, int)> display = [&](Trie* root, char dis[], int depth) {
      	if (root->isEndofWords) {
			dis[depth] = '\0';
			cout << dis << endl;
      	}
      	for (int i = 0; i < ALPHABET; ++i) {
      	 	if (root->children[i]) {
      	 	 	dis[depth] = i + 'a';
      	 	 	display(root->children[i], dis, depth + 1);
      	 	}
      	}
    };
    function<Trie*(Trie*, string, int)> remove = [&](Trie* root, string key, int depth) {
		auto isEmpty = [&](Trie* root) {
    	  	for (int i = 0; i < ALPHABET; ++i) {
    	 	    if (root->children[i]) {
    	 	      	return false;
    	 	     }
    	 	 }
    	 	 return true;
    	 };   	
    	if (!root) {
    	 	return root;
    	}
    	if (depth == (int) key.length()) {
    	 	if (root->isEndofWords) {
    	 		root->isEndofWords = false;
    	 	}    	 
    	 	if (isEmpty(root)) {
				delete (root);
				root = NULL;
    	 	}
    	 	return root;
    	}
    	int index = key[depth] - 'a';
    	root->children[index] = remove(root->children[index], key, depth + 1);
    	if (isEmpty(root) and root->isEndofWords == false) {
    	 	delete (root);
    	 	root = NULL;
    	}
    	return root;
    };
    auto searching = [&](struct Trie* root, string key) {
		struct Trie* pCrawl = root;
		for (int i = 0; i < (int) key.length(); ++i) {
 	  	 	int index = key[i] - 'a';
 	  	 	if (!pCrawl->children[index]) {
				return false;
 	  	 	}
 	  	 	pCrawl = pCrawl->children[index];
 	  	}
 	  	return (pCrawl != NULL and pCrawl->isEndofWords);
 	};
    build();
    char dis[30];
    display(root, dis, 0);
    string str = "by";
    remove(root, str, 0);
    cout << "After deleting " << str << endl; 	
    display(root, dis, 0);
    cin >> q;
 	for (int i = 0; i < q; ++i) {
		cin >> str;
		cout << str << endl;
		searching(root, str) ? cout << str << " found!\n" : cout << str << " not found!\n";
 	}
}
int main() {
    ios::sync_with_stdio(false);
    solve();
    return 0;
}
