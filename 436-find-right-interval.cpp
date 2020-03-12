class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        map<int, int> mp;
        vector<int> res;
        
        for(int i=0; i<intervals.size(); i++)
            mp[intervals[i][0]] = i;
        
        for(int i=0; i<intervals.size(); i++) {
            auto it = mp.lower_bound(intervals[i][1]);
            if(it != mp.end()) res.push_back(it->second);
            else res.push_back(-1);
        }
        return res;        
    }
};
