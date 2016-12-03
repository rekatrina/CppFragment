#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost::property_tree;

int main(int argc, char **argv){
	vector<int> a;
	ptree pt;

	//read_xml("C:\\Program Files\\MATLAB\\R2015b\\resources\\MATLAB\\en\\filterset.xml", pt);
	
	try{
	
		read_xml("C:\\12.awm", pt);
	
	}
	catch (xml_parser::xml_parser_error sysError){
		
		cout << sysError.line() << sysError.message() << endl;
		return 0;

	}

	ptree pways = pt.get_child("Mission");
	BOOST_FOREACH()

	string value = pways.data();
	cout << value << endl;
	char temp;
	cin >> temp;
	return 1;
}