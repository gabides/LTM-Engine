//
//  txtToVector.cpp
//  LTM-Engine
//
//  Created by Gabriel Dittrick on 18/04/2018.
//  Copyright © 2018 Gabriel Dittrick. All rights reserved.
//

#include "Header.h"


vector<MicroExpression> txtToMEVector(string txtpath)
{
    ifstream file(txtpath);
    string current_line;
    // vector allows you to add data without knowing the exact size beforehand
    
    vector<MicroExpression> MEs;
    // Start reading lines as long as there are lines in the file
    
    while(getline(file, current_line)){
        
        // Now inside each line we need to seperate the cols
        vector<string> values;
        stringstream temp(current_line);
        string single_value;
        MicroExpression me;
        while(getline(temp,single_value,';')){
            values.push_back(single_value);
        }
        
        //put the microExpression info from the string vector to the me object
        me.onset = atoi(values[0].c_str());
 
        if(values[1]=="/" or values[1]=="\\"){values[1] = to_string(atoi(values[0].c_str())+25);}
        
        me.offset = atoi(values[1].c_str());
        me.emotion = values[2];
        if (values[3].length()>2){me.AU = 0;}
        else {me.AU = atoi(values[3].c_str());}
        

        // add the row to the complete data vector
        MEs.push_back(me);
        
    }
    return MEs;
}
