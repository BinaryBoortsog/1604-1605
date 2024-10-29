#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

int main()
{
    // 전체 집합 U를 입력받습니다.
    set<int> U;
    int element;
    while (cin >> element)
    {
        U.insert(element);  // 입력된 요소를 U 집합에 추가
        if (cin.peek() == '\n')  // 줄바꿈 문자가 나오면 종료
            break;
    }

    int m;
    cin >> m;  // 부분 집합의 수를 입력받습니다.

    // 부분 집합들을 저장하는 벡터, 각 부분 집합은 인덱스와 요소 집합으로 구성됩니다.
    vector<pair<int, set<int>>> subsets(m);
    for (int i = 0; i < m; ++i)
    {
        int index;
        cin >> index;  // 부분 집합의 인덱스를 입력받습니다.
        set<int> subset_elements;
        while (cin >> element)
        {
            subset_elements.insert(element);  // 부분 집합의 요소를 입력받아 저장
            if (cin.peek() == '\n')  // 줄바꿈 문자가 나오면 종료
                break;
        }
        subsets[i] = {index, subset_elements};  // 벡터에 인덱스와 요소 집합을 저장
    }

    set<int> covered;  // 선택된 부분 집합들로 덮인 전체 요소를 저장하는 집합
    vector<int> selected_indices;  // 선택된 부분 집합의 인덱스를 저장

    // 전체 집합 U가 덮일 때까지 반복
    while (covered.size() < U.size())
    {
        int best_index = -1;  // 이번 단계에서 최선의 부분 집합 인덱스
        int max_cover = 0;  // 이번 단계에서 덮을 수 있는 최대 새 요소 개수
        set<int> best_subset;  // 이번 단계에서 최선의 부분 집합

        // 각 부분 집합을 검사
        for (int i = 0; i < m; ++i)
        {
            int index = subsets[i].first;
            const set<int> &subset = subsets[i].second;
            set<int> new_elements;

            // 부분 집합에서 아직 덮이지 않은 요소를 새로운 요소 집합에 추가
            for (const auto &elem : subset)
            {
                if (covered.find(elem) == covered.end())
                {
                    new_elements.insert(elem);
                }
            }

            // 덮을 수 있는 요소가 더 많은 경우 또는 요소가 같을 경우 인덱스가 작은 순서로 선택
            if (new_elements.size() > max_cover)
            {
                max_cover = new_elements.size();
                best_index = index;
                best_subset = new_elements;
            }
            else if (new_elements.size() == max_cover && index < best_index)
            {
                best_index = index;
                best_subset = new_elements;
            }
        }

        // 최선의 부분 집합이 선택되었으면 인덱스를 저장하고 요소들을 덮인 집합에 추가
        if (best_index != -1)
        {
            selected_indices.push_back(best_index);
            covered.insert(best_subset.begin(), best_subset.end());
        }
        else
        {
            break;
        }
    }

    // 선택된 부분 집합들의 인덱스를 출력
    for (const auto &index : selected_indices)
    {
        cout << index << " ";
    }
    cout << endl;

    // 선택된 부분 집합의 총 개수 출력
    cout << selected_indices.size() << endl;

    return 0;
}
