#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 아이템 구조체 정의: 무게, 가치, 인덱스를 저장
struct Item
{
    int weight, value, index;
    Item(int w, int v, int i) : weight(w), value(v), index(i) {}
};

// 비교 함수: 가치를 무게로 나눈 비율을 기준으로 내림차순 정렬
bool compare(Item a, Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// 부분 배낭 문제 해결 함수
void fractionalKnapsack(int capacity, vector<Item> &items)
{
    // 가치/무게 비율을 기준으로 아이템 정렬
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;                  // 배낭에 담은 총 가치
    vector<pair<int, double>> selectedItems;  // 선택된 아이템과 그 비율

    // 정렬된 아이템 목록을 순회하면서 배낭에 아이템 추가
    for (const auto &item : items)
    {
        if (capacity == 0)  // 배낭 용량이 0이면 종료
            break;

        if (item.weight <= capacity)  // 아이템 전체를 배낭에 넣을 수 있는 경우
        {
            capacity -= item.weight;            // 배낭 용량 감소
            totalValue += item.value;           // 총 가치에 아이템 가치 추가
            selectedItems.push_back({item.index, 1.0}); // 아이템 전체 선택
        }
        else  // 일부만 넣을 수 있는 경우
        {
            double fraction = (double)capacity / item.weight;  // 넣을 수 있는 비율 계산
            totalValue += item.value * fraction;               // 총 가치에 비율만큼의 가치 추가
            selectedItems.push_back({item.index, fraction});   // 아이템의 일부 선택
            break;
        }
    }

    // 선택된 아이템과 그 비율을 출력
    for (const auto &selected : selectedItems)
    {
        cout << selected.first << " " << fixed << setprecision(1) << selected.second << endl;
    }
    cout << fixed << setprecision(0) << totalValue << endl; // 총 가치 출력
}

int main()
{
    int n;  // 아이템 개수
    cin >> n;

    vector<Item> items;  // 아이템 리스트

    // 아이템 정보 입력
    for (int i = 0; i < n; ++i)
    {
        int weight, value;
        cin >> weight >> value;
        items.push_back(Item(weight, value, i));
    }

    int capacity;  // 배낭 용량
    cin >> capacity;

    fractionalKnapsack(capacity, items);  // 부분 배낭 문제 해결 함수 호출

    return 0;
}
