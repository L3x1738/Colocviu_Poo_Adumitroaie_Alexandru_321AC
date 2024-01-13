#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>
///Testare
using namespace std;

template<typename T>
class Calculator {
public:
    T add(T a, T b) {
        return a + b;
    }

    T sub(T a, T b) {
        return a - b;
    }

    T mul(T a, T b) {
        return a * b;
    }

    T div(T a, T b) {
        if (b == 0) {
            std::cout << "Division By Zero" << std::endl;
            return static_cast<T>(0);
        } else {
            return a / b;
        }
    }

    T mini(T a, T b) {
        return (a < b) ? a : b;
    }

    T maxi(T a, T b) {
        return (a > b) ? a : b;
    }
};

class Step {
private:
string name;
public:

    virtual void set_param()
{

}
    virtual void execute() 
    {

    }

    virtual ~Step() = default;
    void set_name(string n)
    {
        this->name=n;
    }
    string get_name() const
    {
        return name;
    }

    virtual string to_file()
    {

    }

    virtual string save_file()
    {

    }

};

class TitleStep: public Step{
private:
    string title;
    string subtitle;
public:
    void set_param()
    {
        string t,st;
        cout<<"Please enter the title ";
        cin>>t;
        cout<<"Please enter the subtitle";
        cin>>st;
        title=t;
        subtitle=st;
    }
    void execute(){
        cout<<get_name()<<" step with title: "<<title<<" and subtitle: "<<subtitle<<endl;
    }
    string to_file()
    {
        string line=get_name()+" step with title "+title+" and subtitle: "+subtitle;
        return line;
    }
    string save_file()
    {
        string line=get_name()+":"+title+"-"+subtitle+"-";
        return line;
        
    }
    TitleStep(string t,string st)
    {
        title=t;
        subtitle=st;
    }
    TitleStep()
    {
        title="";
        subtitle="";
    }
};

class TextStep: public Step{
private:
    string title;
    string copy;
public:
   void set_param()
    {
        string t,cp;
        cout<<"Please enter the title ";
        cin>>t;
        cout<<"Please enter the copy";
        cin>>cp;
        title=t;
        copy=cp;
    }

    void execute() {
        cout<<get_name()<<" step with title: "<<title<<" and copy: "<<copy<<endl;
    }

    string to_file()
    {
        string line=get_name()+" step with title "+title+" and copy "+copy;
        return line;
    }

        string save_file()
    {
        string line=get_name()+":"+title+"-"+copy+"-";
        return line;
        
    }
        void read_from_file(string t,string c)
    {
        title=t;
        copy=c;
        
    }
    TextStep(string t, string cp)
    {
        title=t;
        copy=cp;
    }
    TextStep()
    {
        title="";
        copy="";
    }
};

class TextInputStep: public Step{
private:
    string description;
    string text_input;
public:
       void set_param()
    {
        string d;
        cout<<"Please enter the description ";
        cin>>d;
        description=d;
    }
    void execute(){
        string ti;
        cout<<"Please enter the text input";
        cin>>ti;
        text_input=ti;
        cout<<get_name()<<" step with description: "<<description<<" and input: "<<text_input<<endl;
    }

    string to_file()
    {
        string line=get_name()+" step with description "+description+" and input "+text_input;
        return line;
    }

     string save_file()
    {
        string line=get_name()+":"+description+"-";
        return line;
        
    }

        void read_from_file(string d,string ti)
    {
        description=d;
        text_input=ti;
    }
    TextInputStep(string d)
    {
        description=d;
    }
    TextInputStep()
    {
        description="";
    }
};

class NumberInputStep: public Step{
private:
    string description;
    float number_input;
public:
        void set_param()
    {
        string d;

        cout<<"Please enter the description ";
        cin>>d;

        description=d;
        
    }
    void execute() {
        int ok = 0;
        while (ok == 0) {
            try {
                cout << "Please enter the number input: ";
                float ni;
                cin >> ni;

                if (cin.fail()) {
                    cin.clear();            // Clear the error state
                    cin.ignore(INT_MAX, '\n'); // Ignore invalid input
                    throw invalid_argument("Error: Input not a float");
                }

                ok = 1;
                number_input = ni;
                cout << get_name() << " step with description: " << description << " and input: " << number_input << endl;
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
    float get_val()
    {
        return number_input;
    }

        string to_file()
    {
        string line=get_name()+" step with description "+description+" and input "+to_string(number_input);
        return line;
    }
        string save_file()
    {
        string line=get_name()+":"+description+"-";
        return line;
        
    }
        void read_from_file(string d,float ni)
    {
        description=d;
        number_input=ni;
    }
    NumberInputStep(string d)
    {
        description=d;

    }
    NumberInputStep()
    {
        description="";
    }
};




class TextFileStep: public Step{
private:
    string description;
    string file_name;
public:
   void set_param()
    {
        string d;
        cout<<"Please enter the description ";
        cin>>d;

        description=d;
        
    }
    void execute()  {
        string fn;
        int ok=0;
while(ok==0)
       { try{
        cout<<"Please enter the file name(.txt): ";
        cin>>fn;
        if(fn.substr(fn.length()-4)!=".txt")
        throw invalid_argument("Error: Invalid extension");
        ok=1;
        file_name=fn;
        cout<<"file "<<file_name<<" has been added with the description: "<<description<<endl;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
    }}
    }
    string get_txt_name()
    {
        return file_name;
    }
        
        string to_file()
    {
        string line=get_name()+" step with description "+description+" and filename "+file_name;
        return line;
    }
        string save_file()
    {
        string line=get_name()+":"+description+"-";
        return line;
        
    }
        void read_from_file(string d,string fn)
    {
        description=d;
        file_name=fn;
    }
    TextFileStep(string d)
    {
        description=d;
    }
    TextFileStep()
    {
        description="";
    }
};

class  CSVFileStep: public Step{
private:
    int step;
    string description;
    string file_name;
public:
      void set_param()
    {
        string d;
        cout<<"Please enter the description ";
        cin>>d;

        description=d;
        
    }
    void execute() {
        string fn;
        int ok=0;
        while(ok==0)
        {
        try{
        cout<<"Please enter the file name(.csv)";
        cin>>fn;
        if(fn.substr(fn.length()-4)!=".csv")
        throw invalid_argument("Error: Invalid extension");
        file_name=fn;
        ok=1;
       cout<<"file "<<file_name<<" has been added with the description: "<<description<<endl;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }}
    string get_csv_name()
    {   
        
        return file_name;
       
    }

    string to_file()
    {
        string line=get_name()+" step with description "+description+" and filename "+file_name;
        return line;
    }
        string save_file()
    {
        string line=get_name()+":"+description+"-";
        return line;
        
    }
     void read_from_file(string d,string fn)
    {
        description=d;
        file_name=fn;
    }

    CSVFileStep(string d)
    {
        description=d;
    }
    CSVFileStep()
    {
        description="";
    }
};



class EndStep : public Step {
public:
    void execute(){
        cout << "End Step" <<endl;
    }
    string to_file()
    {
        return "End Step";
    }
    string save_file()
    {
        return "EndStep:";
    }
};

class ProcessBuilder {
private:
    vector<Step*> steps;
    string name;
    string description;
public:
    void set_stuff(string n,string d)
    {
        name=n;
        description=d;
    }
    string get_name()
    {
        return name;
    }
    string get_desc()
    {
        return description;
    }
    ~ProcessBuilder() {
        for (auto& step : steps) {
            delete step;
        }
    }

    void addStep(Step* step) {
        steps.push_back(step);
    }

    void executeSteps() const {
        for (const auto& step : steps) {
            cout<<"do you want to execute step "<<step->get_name()<<"? (y/n)";
            char choice;
            cin>>choice;
            if(choice=='y')
            step->execute();
            else cout<<"skipping step "<<endl;
        }
    }

    Step* getStep(int i) const
    {
        return steps[i];
    }

    vector<Step*> get_current_steps() const{
        vector<Step*> crr_steps;
        crr_steps=steps;
        return crr_steps;
    }
    void add_flow()
    {   string n,d;
        cout<<"Please enter the name for the flow ";
        cin>>n;
        cout<<"Please enter the description ";
        cin>>d;
        name=n;
        description=d;
        ofstream f;
    f.open("flows.csv", ios::app);
    f<<n<<','<<d<<',';
    for (const auto& step : steps)
    {
        f << step->save_file();
        f<<',';
    }
    f << endl;
    f.close();
    }
     void clearSteps() {
        for (auto& step : steps) {
            delete step;
        }
        steps.clear();
    }
};


class CalculusStep: public Step{
private:
    vector<int>v;
    string operation;
    float result;
    vector <Step*> x;
public:
    CalculusStep(vector <Step*> pb)
    {
        x=pb;
    }
    void set_param()
    {
    
    }

   void execute()  {
    string op;
        vector<int> steps;
        int number;
        cout<<"please enter the number of steps: ";
       do {cin>>number;}while(number<0);

        for (int i=0;i<number;i++)
        {   int step;
            cout<<"Please enter step no "<<i+1<<": ";
            do{cin>>step;
            if(step>=x.size()||x[step]->get_name()!="NumberInput")
            cout<<"Step is not valid. Please enter NumbetInput step"<<endl;
                }while(step>=x.size()||x[step]->get_name()!="NumberInput");
            steps.push_back(step);
        }
        cout<<"Please enter the operation";
        do {
    cin >> op;
} while (op != "+" && op != "-" && op != "/" && op != "*" && op != "min" && op != "max");
        operation=op;
        v=steps;
    int n = v.size();
    float numberInputs[n];

    for (int i = 0; i < n; i++) {
        int step = v[i];
        NumberInputStep *numStep = dynamic_cast<NumberInputStep*>(x[step]);
        numberInputs[i] = numStep->get_val();
    }

    Calculator<float> c;
    if(operation=="+")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.add(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }

    if(operation=="-")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.sub(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }
    if(operation=="*")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.mul(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }

        if(operation=="/")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.div(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }

            if(operation=="min")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.mini(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }

        if(operation=="max")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.maxi(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }
}

        string to_file()
    {
        string line=get_name()+" step with steps ";
        for (int i=0;i<v.size();i++)
            {
                line+=to_string(v[i]);
                line+=" ";
            }
        line+="and operation ";
        line+=operation;
        return line;
    }

         string save_file()
    {
        string line=get_name()+":";
        return line;
        
    }
};

class DisplayStep: public Step{
private:
    int step;
    vector <Step*> x;
public:

    DisplayStep(vector <Step*> pb)
    {
        x=pb;
    }
   void set_param()
    {
        
    }
    void execute() {
        int chosenStep;
        cout<<"Please enter the file step to open: ";
       cin >> chosenStep;

    while (chosenStep < 0 || chosenStep >= x.size() ||
           (x[chosenStep]->get_name() != "CSVFileStep" && x[chosenStep]->get_name() != "TextFileStep")) {
        cout << "Invalid step number. Please enter a valid step number: ";
        cin >> chosenStep;
    }

  
    step = chosenStep;
        if(x[step]->get_name()=="CSVFileStep")
           {
             CSVFileStep *CSVStep = dynamic_cast<CSVFileStep*>(x[step]);
                ifstream inputFile(CSVStep->get_csv_name());
                string line;
             while (getline(inputFile, line)) {
            cout << line << endl;
        }
           }

        else 
        {
            TextFileStep *TextStep = dynamic_cast<TextFileStep*>(x[step]);
                ifstream inputFile(TextStep->get_txt_name());
                string line;
             while (getline(inputFile, line)) {
            cout << line << endl;
        }
    }

}
        string to_file()
    {
        string line=get_name()+" step: displayed the content of the file in step "+to_string(step);
        return line;
    }
    
        string save_file()
    {
        string line=get_name()+":";
        return line;
        
    }
};

class  OutputStep: public Step{
private:
    vector <int> s;
    string file_name;
    string title;
    string description;
    vector <Step*>x;

public:
    OutputStep(vector <Step*> pb,string fn,string t,string d)
    {
        x=pb;
        file_name=fn;
        title=t;
        description=d;
    }

       void set_param()
    {
        
        string d,fn,t;
        
        
        cout<<"Please enter the file name";
        cin>>fn;
        cout<<"Please enter the title for the file: ";
        cin>>t;
        cout<<"Please enter the description for the file: ";
        cin>>d;
        description=d;
        file_name=fn;
        title=t;
    }   
    void execute() {
        vector <int> steps;
        int number;
        cout<<x.size();
        cout<<"Please enter the number of steps: ";
        cin>>number;
        for (int i=0;i<number;i++)
        {   int step;
            cout<<"Please enter step no "<<i+1<<": ";
            do{cin>>step;
            if(step>=x.size())
            cout<<"Step is not valid"<<endl;
                }while(step>=x.size());
            steps.push_back(step);
        }
        s=steps;
        ofstream f;
        f.open(file_name);
        f<<title<<endl<<description<<endl<<endl;
        for(int i=0;i<s.size();i++)
        f<<x[s[i]]->to_file()<<endl;
        f.close();
    }

    string to_file()
    {
        string line=get_name()+" step. Wrote steps: ";
        for(int i=0;i<s.size();i++)
        {
            line+=to_string(s[i]);
            line+=",";
        }
        return line;
    }

    string save_file()
    {
        string line=get_name()+":"+file_name+"-"+title+"-"+description+"-";

    return line;
    }

    OutputStep(string fn, string d,string t)
    {
        file_name=fn;
        title=t;
        description=d;
    }
    OutputStep(vector <Step*> pb)
    {
        x=pb;
    }
};

int main(){ 

     ProcessBuilder processBuilder;
     vector<vector<string>> Testmatrix;
     //{{"Title:saut-buna-","NumberInput:niciodata-","CSVFileStep:odata-","CalculusStep:","TextFileStep:da-","DisplayStep:","OutputStep:nume.txt-titlunum-descrierebuna-","EndStep:"}};
    string line;

    ifstream file("flows.csv");
    while (std::getline(file, line)) {
        
        std::stringstream ss(line);

        std::vector<std::string> columns;

        
        std::string column;
        while (std::getline(ss, column, ',')) {
            columns.push_back(column);
        }

        Testmatrix.push_back(columns);
    }
    file.close();


int option=0;

while (option != 4) {
        cout << "Welcome to my application for creating flows. Please choose an option:" << endl;
        cout << "1. Create a flow." << endl;
        cout << "2. Use a flow" << endl;
        cout << "3. Delete a flow" << endl;
        cout << "4. Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                processBuilder.clearSteps();
                int step = 0;
                while (step != 10) {
                    cout << "\n1. Title step" << endl;
                    cout << "2. Text step" << endl;
                    cout << "3. Text Input step" << endl;
                    cout << "4. Number Input step" << endl;
                    cout << "5. Calculus step" << endl;
                    cout << "6. Text File Input step" << endl;
                    cout << "7. CSV File Input step" << endl;
                    cout << "8. Display step" << endl;
                    cout << "9. Output step" << endl;
                    cout << "10. End step" << endl << endl;
                    cout << "Please choose a step to add: ";
                    cin >> step;

                    switch (step) {
                        case 1: {
                            Step *a = new TitleStep();
                            a->set_param();
                            a->set_name("Title");
                            processBuilder.addStep(a);
                            
                            cout<<"Title step added.Press enter to continue";
                            cin.ignore(1000000000, '\n');
                            cin.ignore(1000000000, '\n');

                            break;
                        }
                        case 2: {
                            Step *a = new TextStep();
                            a->set_param();
                            a->set_name("TextStep");
                            processBuilder.addStep(a);
                            cout<<"text step has been added. Press enter to continue";
                            cin.ignore(1000000000, '\n');
                            cin.ignore(1000000000, '\n');
                            break;
                        }
                        case 3: {
                            Step *a = new TextInputStep();
                            a->set_param();
                            a->set_name("TextInputStep");
                            cout<<"text input step has been added. Press enter to continue";
                            cin.ignore(1000000000, '\n');
                            processBuilder.addStep(a);
                            break;
                        }
                        case 4: {
                            Step *a = new NumberInputStep();
                            a->set_param();
                            a->set_name("NumberInput");
                            cout<<"number input step has been added. Press enter to continue";
                            cin.ignore(1000000000, '\n');
                            processBuilder.addStep(a);
                            break;
                        }
                        case 5: {
                            Step *a = new CalculusStep(processBuilder.get_current_steps());
                            a->set_name("CalculusStep");
                            cout<<"Calculus step has been added. Press enter to continue";
                            cin.ignore(1000000000, '\n');
                            processBuilder.addStep(a);
                            break;
                        }
                        case 6: {
                            Step *a = new TextFileStep();
                            a->set_name("TextFileStep");
                            a->set_param();
                            cout<<"Text File step has been added. Press enter to continue";
                            cin.ignore(1000000000, '\n');
                            processBuilder.addStep(a);
                            break;
                        }
                        case 7: {
                            Step *a = new CSVFileStep();
                            a->set_name("CSVFileStep");
                            a->set_param();
                            cout<<"CSV file step has been added. Press enter to continue";
                            cin.ignore(1000000000, '\n');
                            processBuilder.addStep(a);
                            break;
                        }
                        case 8: {
                            Step *e = new DisplayStep(processBuilder.get_current_steps());
                            e->set_name("DisplayStep");
                            cout<<"Display step has been added. Press enter to continue";
                            cin.ignore(1000000000, '\n');
                            processBuilder.addStep(e);
                            break;
                        }
                        case 9: {
                            Step *out = new OutputStep(processBuilder.get_current_steps());
                            out->set_name("OutputStep");
                            out->set_param();
                            cout<<"output step has been added. Press enter to continue";
                            cin.ignore(1000000000, '\n');
                            processBuilder.addStep(out);
                            break;
                        }
                        case 10: {
                            Step *end = new EndStep();
                            end->set_name("EndStep");
                            cout<<"End step has been added. Press enter to continue";
                            cin.ignore(1000000000, '\n');
                            processBuilder.addStep(end);
                            break;
                        }
                        default:
                            cout << "Invalid Step" << endl;
                            break;
                    }
                }
                processBuilder.add_flow();
                vector <string> coloane;
                coloane.push_back(processBuilder.get_name());
                coloane.push_back(processBuilder.get_desc());
                for(auto& step: processBuilder.get_current_steps())
                    coloane.push_back(step->save_file());
                Testmatrix.push_back(coloane);

                
                break;
            }

            case 2:
            {
                processBuilder.clearSteps();
                int x;
                cout<<"please enter the flow you want to use";
                cin>>x;
                processBuilder.set_stuff(Testmatrix[x][0],Testmatrix[x][1]);
                for(size_t i=2;i<Testmatrix[x].size();i++)
{
    string word;
    istringstream iss(Testmatrix[x][i]);
    getline(iss,word,':');

    if(word=="Title")
    {
    string t,desc;
    getline(iss,word,'-');
        t=word;
    getline(iss,word,'-');
    desc=word;  
     Step *a=new TitleStep(t,desc);
    a->set_name("Title");    
    processBuilder.addStep(a);
    
    

    }
    if(word=="TextStep")
    {
        string t,cp;
        getline(iss,word,'-');
        t=word;
        getline(iss,word,'-');
        cp=word;
        Step *a=new TextStep(t,cp);
        a->set_name("TextStep");
        processBuilder.addStep(a);
        
    }

    if(word=="TextInputStep")
    {
        string d;
        getline(iss,word,'-');
        d=word;
        Step *a=new TextInputStep(d);
        a->set_name("TextInputStep");
        processBuilder.addStep(a);
        
    }

    if(word=="NumberInput")
    {
    string desc;
    float n;
    getline(iss,word,'-');
        desc=word;  
     Step *a=new NumberInputStep(desc);
    a->set_name("NumberInput");    
    processBuilder.addStep(a);
    

    }

    if(word=="CSVFileStep")
    {
        string desc;
        getline(iss,word,'-');
        desc=word;
        Step *a=new CSVFileStep(desc);
        a->set_name("CSVFileStep");
        processBuilder.addStep(a);
        
    }
    if(word=="TextFileStep")
    {
        string desc;
        getline(iss,word,'-');
        desc=word;
        Step *a=new TextFileStep(desc);
        a->set_name("TextFileStep");
        processBuilder.addStep(a);
        
    }
    if(word=="CalculusStep")
    {
        Step *a=new CalculusStep(processBuilder.get_current_steps());
        a->set_name("CalculusStep");
        processBuilder.addStep(a);
        
    }
    if(word=="DisplayStep")
    {
        Step *a=new DisplayStep(processBuilder.get_current_steps());
        a->set_name("DisplayStep");
        processBuilder.addStep(a);
        
    }
    if(word=="OutputStep")
    {
        string fn,d,t;
        getline(iss,word,'-');
        fn=word;
        getline(iss,word,'-');
        t=word;
        getline(iss,word,'-');
        d=word;
        
        Step *a=new OutputStep(processBuilder.get_current_steps(),fn,t,d);
        
    }
    if(word=="EndStep")
    {
        Step *a=new EndStep();
        a->set_name("EndStep");
        processBuilder.addStep(a);
        
    }
}
processBuilder.executeSteps();
                break;
            }
            case 3:
            {
            
                cout<<"please enter the flow you want to delete: ";
size_t rowToDelete ;
cin>>rowToDelete;
    // Check if the row index is valid
    if (rowToDelete < Testmatrix.size()) {
        // Use erase to remove the row
        Testmatrix.erase(Testmatrix.begin() + rowToDelete);

        // Display the updated matrix
        for (const auto& row : Testmatrix) {
            for (const auto& column : row) {
                std::cout << column << " ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cerr << "Invalid row index." << std::endl;
    }

    ofstream g("flows.csv");
    for (const auto& row : Testmatrix) {
        for (const auto& column : row) {
            g << column << ",";
        }
        g << std::endl;
    }
g.close();
           break;
            }
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
    
    ///processBuilder.executeSteps();

   /* flow1.open("flow1.txt");
    string line;
     while (getline(flow1, line)) 
     {
        string word;
        istringstream iss(line);
        getline(iss,word,':');
        cout<<word<<endl;
        while(getline(iss,word,','))
        {
            cout<<word<<endl;
        }
        cout<<endl;
     }*/
    /* Step *a=new TitleStep;
     a->set_param();
     a->set_name("Title");

     processBuilder.addStep(a);
    
   Step *b=new NumberInputStep();
    b->set_param();
    b->set_name("NumberInput");
    processBuilder.addStep(b);


    Step *d=new NumberInputStep();
    d->set_param();
    d->set_name("NumberInput");
    processBuilder.addStep(d);


     Step *z=new TitleStep;
     z->set_param();
     z->set_name("Title");
     processBuilder.addStep(z);

     
    Step *calc = new CalculusStep(processBuilder.get_current_steps());
    calc->set_param();
    calc->set_name("CalculusStep");
    processBuilder.addStep(calc);

    ///calc->execute();
   
     Step *r=new CSVFileStep();
    r->set_name("CSVFileStep");
    r->set_param();
    ///r->execute();
    processBuilder.addStep(r);


    Step *f=new TextFileStep();
    f->set_name("TextFileStep");
    f->set_param();
    ///f->execute();
    processBuilder.addStep(f);


    Step* e=new DisplayStep(processBuilder.get_current_steps());
    e->set_param();
    e->set_name("DisplayStep");
    processBuilder.addStep(e);

    ///e->execute();
    Step* out=new OutputStep(processBuilder.get_current_steps());
    out->set_name("OutputStep");
    out->set_param();
    processBuilder.addStep(out);


processBuilder.executeSteps();*/
 

}
