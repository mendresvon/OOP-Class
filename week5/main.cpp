#include <iostream>
using namespace std;


string convert(int score) {
	string grade;
	if (score >= 90) {
		grade = "A";
	}
	else if (score >= 80) {
		grade = "B";
	}
	else if (score >= 70) {
		grade = "C";
	}
	else if (score >= 60) {
		grade = "D";
	}
	else {
		grade = "E";
	}


	//使用switch case改寫以上範例
	//switch (score / 10) {
	//	case 10:
	//	case 9:
	//		grade = "A";
	//		break;
	//	case 8:
	//		grade = "B";


	//		break;
	//	case 7:
	//		grade = "C";
	//		break;
	//	case 6:
	//		grade = "D";
	//		break;
	//	default:
	//		grade = "E";
	//		break;
	//}
	//trinary operator
	// (condition) ? true : false;
	//grade = (score >= 90) ? "A" : (score >= 80) ? "B" : (score >= 70) ? "C" : (score >= 60) ? "D" : "E";
	return grade;
}

int main()
{
	// 給定一個分數，輸出對應的等第
	int score = 0;


	cout << "請輸入一個分數: ";
	cin >> score;
	string grade = convert(score);


	cout << "分數為: " << score << endl;
	cout << "等第為: " << grade << endl;
	string isPass;
	isPass = (score >= 60) ? "及格" : "不及格";
	cout << "是否及格: " << isPass << endl;
}