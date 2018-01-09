struct Node{
    string feature_name;
    int featureIndex;
    vector<Node*> child;
    
    Node(){}
    void set(string label){
        feature_name = label;
    }
    void set(string label, int index){
        feature_name = label;
        featureIndex = index;
    }
    
    string getLabel(){
		return feature_name;
	}
    int getFeatureIndex(){
		return featureIndex;
	}
};

struct DecisionTree{
    Node *root;
    DecisionTree(){
        root = new Node();
    }
};

struct Example{
    vector<int> exp;

    int getFeatureVal(int featureIndex) {return exp[featureIndex];}
    int getClass(){return exp[exp.size()-1]; }
};

