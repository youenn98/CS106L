#include <utility>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include "wikiscraper.h"


using std::cout;            using std::endl;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;   using std::pair;

int common_page(unordered_set<string> &pgset,unordered_set<string> &end_set){
    int cnt = 0;
    for(auto &s:pgset){
        if(end_set.count(s)) cnt++;
    }
    return cnt;
}

vector<string> dele_cnt(vector<pair<string,int>> &vp){
    vector<string> ret;
    for(auto &p:vp){
        ret.push_back(p.first);
    }
    return ret;
}

/*
 * This is the function you will be implementing. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */
vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    WikiScraper wikiScrapter;
    auto end_set = wikiScrapter.getLinkSet(end_page);
    unordered_set<string> searched_page;

    auto compare = [](const vector<pair<string,int>> &v1,const vector<pair<string,int>> &v2){
        if(v1.size() == 0 || v2.size() == 0) return true;
        pair<string,int> last1 = v1[v1.size()-1];
        pair<string,int> last2 = v2[v2.size()-1];
        if(last1.second < last2.second) return true;
        else if(last1.second > last2.second) return false;
        else return v1.size() > v2.size();
    };

    priority_queue<vector<pair<string,int>>,vector<vector<pair<string,int>>>, decltype(compare)> pq(compare);
    auto st_set = wikiScrapter.getLinkSet(start_page);

    int cnt = common_page(st_set,end_set);
    vector<pair<string,int>> ladder_init;
    ladder_init.push_back({start_page,cnt});
    pq.push(ladder_init);
    while(!pq.empty()){
        auto temp_ladder = pq.top();pq.pop();
        pair<string,int> last_page = temp_ladder[temp_ladder.size()-1];
        searched_page.insert(last_page.first);
        auto linkset = wikiScrapter.getLinkSet(last_page.first);
        vector<string> next_to_add;

        for(const string &s : linkset){
            if(searched_page.count(s)) continue;
            searched_page.insert(s);
            //cout << s << endl;
            if(s == end_page){
                auto new_ladder = temp_ladder;
                new_ladder.push_back({s,-1});
                return dele_cnt(new_ladder);
            }else{
                next_to_add.push_back(s);
            }
        }
        //cout << "pp" << endl;
        for(auto &s:next_to_add){
            auto new_ladder = temp_ladder;
            auto new_link_set = wikiScrapter.getLinkSet(s);
            int c_page = common_page(new_link_set,end_set);
            new_ladder.push_back({s,c_page});
            pq.push(new_ladder);
        }
    }

    return {};
}



int main() {
    auto ladder = findWikiLadder("Milkshake", "Gene");
    cout << endl;

    if(ladder.empty()) {
        cout << "No ladder found!" << endl;
    } else {
        cout << "Ladder found:" << endl;
        cout << "\t";
        for(auto &s:ladder){
            cout << s << " ";
        }
        cout << endl;

    }

    return 0;
}




