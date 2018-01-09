#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define mem(list, val) memset(list, (val), sizeof(list))
#define pb push_back

#include "objects.hpp"
#include "utilities.hpp"
#include "DecisionTree_utilities.hpp"

void crossValidate(vector <Example> Examples)
{
    int testDataSize = Examples.size()/5;
    vector<Example> data[5];
    
    for(int i=0; i<5; i++){
		if(i != 4) data[i].insert(data[i].end(), Examples.begin()+i*testDataSize, Examples.begin()+(i+1)*testDataSize);
		else data[i].insert(data[i].end(), Examples.begin()+i*testDataSize, Examples.end());
	}

    double sumAccuracy = 0, sumTPR = 0, sumTNR = 0, sumPPV = 0, sumNPV = 0, sumFPR = 0, sumFNR = 0, sumFDR = 0, sumF1 = 0;

    for(int i=0; i<5; i++){

        //******************* processing ***************************//

		vector<Example> Examples;
		for(int j=0; j<5; j++){
			if(j == i) continue;
			Examples.insert(Examples.end(), data[j].begin(), data[j].end());
		}
		
		createDT(Examples); //Creating the decision tree

		int true_positive = 0, false_negative = 0, false_positive = 0, true_negative = 0;
		
		for(int j=0; j<data[i].size(); j++){
            string prediction = predict(data[i][j]); //making prediction by decision tree

            if(prediction == "yes" && data[i][j].getClass() == 1){
                true_positive++;
            }
            else if(prediction == "yes" && data[i][j].getClass() == 0){
                false_positive++;
            }
            else if(prediction == "no" && data[i][j].getClass() == 1){
                false_negative++;
            }
            else{
                true_negative++;
            }
        }

        //******************** reporting *************************//

        int condition_positive = true_positive + false_negative, condition_negative = false_positive + true_negative;
        int test_outcome_positive = true_positive + false_positive, test_outcome_negative = false_negative + true_negative;

        assert(condition_positive + condition_negative == data[i].size());
        assert(test_outcome_positive + test_outcome_negative == data[i].size());

        double accuracy = 100.0*(true_positive + true_negative)/data[i].size(), //High is GOOD
        TPR = 100.0*true_positive/condition_positive, //High is GOOD
        TNR = 100.0*true_negative/condition_negative, //High is GOOD
        PPV = 100.0*true_positive/test_outcome_positive, //High is GOOD 
        NPV = 100.0*true_negative/test_outcome_negative, //High is GOOD

        FPR = 100.0*false_positive/condition_negative, //Low is GOOD 
        FNR = 100.0*false_negative/condition_positive, //Low is GOOD
        FDR = 100.0*false_positive/test_outcome_positive, //Low is GOOD
        F1 = 2.0*true_positive/(2*true_positive + false_positive + false_negative); //Harmonic mean of PPV and TPR

        sumAccuracy += accuracy;
        sumTPR += TPR;
        sumTNR += TNR;
        sumPPV += PPV;
        sumNPV += NPV;
        sumFPR += FPR;
        sumFNR += FNR;
        sumFDR += FDR;
        sumF1 += F1;
        
        cout << "accuracy:\t" << accuracy << endl;
        cout << "TPR:\t" << TPR << endl;
        cout << "TNR:\t" << TNR << endl;
        cout << "PPV:\t" << PPV << endl;
        cout << "NPV:\t" << NPV << endl;

        cout << "FPR:\t" << FPR << endl;
        cout << "FNR:\t" << FNR << endl;
        cout << "FDR:\t" << FDR << endl;
        cout << "F1:\t" << F1 << endl;
        cout << endl;

        //cout << accuracy << " & " << TPR << " & " << TNR << " & " << PPV << " & " << NPV << " & " << FPR << " & " << FNR << " & " << FDR << " & " << F1 << endl; 
		 //BFS();
	}

    cout << "Average:\n";
    cout << "accuracy:\t" << sumAccuracy/5 << endl;
    cout << "TPR:\t" << sumTPR/5 << endl;
    cout << "TNR:\t" << sumTNR/5 << endl;
    cout << "PPV:\t" << sumPPV/5 << endl;
    cout << "NPV:\t" << sumNPV/5 << endl;

    cout << "FPR:\t" << sumFPR/5 << endl;
    cout << "FNR:\t" << sumFNR/5 << endl;
    cout << "FDR:\t" << sumFDR/5 << endl;
    cout << "F1:\t" << sumF1/5 << endl;


    //cout << sumAccuracy/5 << " & " << sumTPR/5 << " & " << sumTNR/5 << " & " << sumPPV/5 << " & " << sumNPV/5 << " & " << sumFPR/5 << " & " << sumFNR/5 << " & " << sumFDR/5 << " & " << sumF1/5 << endl; 
}

void Test(vector<Example> trainExamples, string testFileName)
{
    createDT(trainExamples);

    vector<Example> testExamples;
    readData(testFileName, testExamples);

    int true_positive = 0, false_negative = 0, false_positive = 0, true_negative = 0;

    for(int i=0; i<(int)testExamples.size(); i++){
        string prediction = predict(testExamples[i]); //making prediction by decision tree

        if(prediction == "yes" && testExamples[i].getClass() == 1){
            true_positive++;
        }
        else if(prediction == "yes" && testExamples[i].getClass() == 0){
            false_positive++;
        }
        else if(prediction == "no" && testExamples[i].getClass() == 1){
            false_negative++;
        }
        else{
            true_negative++;
        }
    }

    //******************** reporting *************************//

    int condition_positive = true_positive + false_negative, condition_negative = false_positive + true_negative;
    int test_outcome_positive = true_positive + false_positive, test_outcome_negative = false_negative + true_negative;

    assert(condition_positive + condition_negative == testExamples.size());
    assert(test_outcome_positive + test_outcome_negative == testExamples.size());

    double accuracy = 100.0*(true_positive + true_negative)/testExamples.size(), //High is GOOD
    TPR = 100.0*true_positive/condition_positive, //High is GOOD
    TNR = 100.0*true_negative/condition_negative, //High is GOOD
    PPV = 100.0*true_positive/test_outcome_positive, //High is GOOD 
    NPV = 100.0*true_negative/test_outcome_negative, //High is GOOD

    FPR = 100.0*false_positive/condition_negative, //Low is GOOD 
    FNR = 100.0*false_negative/condition_positive, //Low is GOOD
    FDR = 100.0*false_positive/test_outcome_positive, //Low is GOOD
    F1 = 2.0*true_positive/(2*true_positive + false_positive + false_negative); //Harmonic mean of PPV and TPR

    cout << "accuracy:\t" << accuracy << endl;
    cout << "TPR:\t" << TPR << endl;
    cout << "TNR:\t" << TNR << endl;
    cout << "PPV:\t" << PPV << endl;
    cout << "NPV:\t" << NPV << endl;

    cout << "FPR:\t" << FPR << endl;
    cout << "FNR:\t" << FNR << endl;
    cout << "FDR:\t" << FDR << endl;
    cout << "F1:\t" << F1 << endl;
    cout << endl;
}

int main()
{
    vector<Example> Examples;
    readData("Assignment1_data_set.csv", Examples);
    crossValidate(Examples);

    //Test(Examples, "in.csv"); 
    return 0;
}
