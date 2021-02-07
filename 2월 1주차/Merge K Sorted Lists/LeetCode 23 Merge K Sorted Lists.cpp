/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    int minusHist[10001];
    int plusHist[10001];
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        for(auto &list : lists){
            if(list == 0)continue;
            ListNode* curr = list;
            if(curr->val<0) minusHist[abs(curr->val)]++;
            else plusHist[curr->val]++;
            while(curr->next){
                curr = curr->next;
                if(curr->val<0) minusHist[abs(curr->val)]++;
                else plusHist[curr->val]++;
            }
        }
        ListNode* root = new ListNode();
        ListNode* answer = root;
        for(int i=10000; i>0; i--){
            if(minusHist[i]){
                for(int k=0; k<minusHist[i]; k++){
                    ListNode* curr = new ListNode(-1*i);
                    answer->next = curr;
                    answer = answer->next;
                }

            }
        }
        for(int i=0; i<10001; i++){
            if(plusHist[i]){
                for(int k=0; k<plusHist[i]; k++){
                    ListNode* curr= new ListNode(i);
                    answer->next = curr;
                    answer = answer->next;
                }
            }
        }

        return root->next;
    }

};