DecisionTree *decisionTree;

void DT(Node *node, vector<Example> Exp, list<int> features, string prevMajorityLabel)
{
	int siz = Exp.size(), pos = getPositiveCount(Exp), neg = siz-pos;
    string majorityLabel = (pos >= neg)? "yes": "no";
    
    if(siz == 0){
        node->set(prevMajorityLabel);
        return;
    }

    if(features.size() == 0){
        node->set(majorityLabel);
        return;
    }

    if(neg == 0){
        node->set("yes");
        return;
    }

    if(pos == 0){
        node->set("no");
        return;
    }

    double maxInfoGain = getInformationGain(Exp, features.front());
    int bestFeatureIndex = features.front();

    list<int>::iterator bestIterator = features.begin();
    for(list<int>::iterator it=features.begin(); it!=features.end(); it++){
        double temp = getInformationGain(Exp, *it);
        if(temp > maxInfoGain){
            maxInfoGain = temp;
            bestFeatureIndex = *it;
            bestIterator = it;
        }
    }

    //cout << Features[bestFeatureIndex] << ' ' << maxInfoGain << endl;
    node->set(Features[bestFeatureIndex], bestFeatureIndex);
    features.erase(bestIterator);

    for(int i=1; i<=10; i++){
        vector<Example> temp;
        getFilteredExamples(Exp, bestFeatureIndex, i, temp);

        Node *childNode = new Node();
        node->child.push_back(childNode);

        //getchar();
        DT(childNode, temp, features, majorityLabel);
    }
}

void createDT(vector<Example> Examples)
{
    list<int> features;
    for(int i=0; i<8; i++) features.push_back(i);

	int siz = Examples.size(), pos = getPositiveCount(Examples), neg = siz-pos;
    string majorityLabel = (pos >= neg)? "yes": "no";
    
    decisionTree = new DecisionTree();
    DT(decisionTree->root, Examples, features, majorityLabel);
}

string predict(Node *node, Example test)
{
    if(node->getLabel() == "yes" || node->getLabel() == "no") return node->getLabel();
    int featureIndex = node->getFeatureIndex();

    return predict(node->child[test.getFeatureVal(featureIndex)-1], test);
}

string predict(Example test)
{
    return predict(decisionTree->root, test);
}

void BFS()
{
	queue<Node*> Q;
	Q.push(decisionTree->root);

	bool visited[10];
	mem(visited, false);

	while(!Q.empty()){
		Node *node = Q.front();
		Q.pop();

        cout << node->getLabel() << '\t';

		if(node->getLabel() == "yes" || node->getLabel() == "no"){
			continue;
		}

		for(int i=0; i<node->child.size(); i++) Q.push(node->child[i]);
        //getchar();
    }
    cout << endl;
}
