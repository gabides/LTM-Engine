//
//  txtToVector.cpp
//  LTM-Engine
//
//  Created by Gabriel Dittrick on 18/04/2018.
//  Copyright © 2018 Gabriel Dittrick. All rights reserved.
//

#include "Header.h"


vector<vector<string>> txtToVector(string txtpath)
{
    ifstream file(txtpath);
    string current_line;
    // vector allows you to add data without knowing the exact size beforehand
    vector< vector<string> > all_data;
    // Start reading lines as long as there are lines in the file
    
    while(getline(file, current_line)){
        
        // Now inside each line we need to seperate the cols
        vector<string> values;
        stringstream temp(current_line);
        string single_value;
        while(getline(temp,single_value,';')){
            
            // convert the string element to a integer value
            //values.push_back(atoi(single_value.c_str()));
            //cout << "read : " << single_value << endl;
            values.push_back(single_value);
        }
        // add the row to the complete data vector
        all_data.push_back(values);
        
    }
    //int n = all_data.size();
    
    /*for (int i=0; i<n; i++){
     for (int j = 0; j < 4 ; j++){
     cout << all_data[i][j] << " ";
     }
     cout << endl;
     }*/
    return all_data;
}
