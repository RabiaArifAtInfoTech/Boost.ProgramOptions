// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<boost/program_options.hpp>
#include<boost/program_options/variables_map.hpp>


void on_age(int age)
{
    std::cout << "On age: " << age << '\n';
}

void to_cout(const std::vector<std::string>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>{
        std::cout, "\n"});
}


int main(int argc, const char* argv[])
{

    //try
    //{
    //    boost::program_options::options_description desc{ "Options" };
    //    desc.add_options()
    //        ("help,h", "Help screen")
    //        ("pi", boost::program_options::value<float>()->default_value(3.14f), "Pi")
    //        ("age", boost::program_options::value<int>()->notifier(on_age), "Age");

    //    boost::program_options::variables_map vm;
    //    boost::program_options::store(parse_command_line(argc, argv, desc), vm);
    //    boost::program_options::notify(vm);

    //    if (vm.count("help"))
    //        std::cout << desc << '\n';
    //    else if (vm.count("age"))
    //        std::cout << "Age: " << vm["age"].as<int>() << '\n';
    //    else if (vm.count("pi"))
    //        std::cout << "Pi: " << vm["pi"].as<float>() << '\n';
    //}
    //catch (const boost::program_options::error& ex)
    //{
    //    std::cerr << ex.what() << '\n';
    //}

    try
    {

        // .................... boost::program_options::  ...............
        

        // 1. options_description : A set of option descriptions. This provides convenient interface for adding new option (the add_options) method, and facilities to search for options by name.
            // 2. options_description.add_options

        // 3. :value<datatype>()
            // 4. value<float>()->default_value(3.14f)
            // 5. value<int>()->notifier(on_age)
            // 6. value<float>()->implicit_value
            // 7. value<int>(&age)
            // 8. value<std::vector<std::string>>()->multitoken()->zero_tokens()->composing()
              
        // 9. command_line_parser
            // 10.   parser.options(desc).allow_unregistered().style()
                // 11. command_line_style::default_style
                // 12. command_line_style::allow_slash_for_short
                
        // 13. parsed_options
            // 14. parser.run();
            
        // 15. variables_map
            // 16. vm.count
            // 17. vm.as
            
        // 18. store(parsed_options, vm)
        //     store(parse_command_line(argc, argv, desc), vm)
        // 19. notify
        // 20. boost::program_options::error
  
        int age;

        boost::program_options::options_description desc{ "Allowed Options" };
        desc.add_options()
            ("help,h", "Help screen")
            ("pi", boost::program_options::value<float>()->implicit_value(3.14f), "Pi")
            ("age", boost::program_options::value<int>(&age), "Age")
            ("phone", boost::program_options::value<std::vector<std::string>>()->multitoken()->
                zero_tokens()->composing(), "Phone")
            ("unreg", "Unrecognized options");

        boost::program_options::command_line_parser parser{ argc, argv };
        parser.options(desc).allow_unregistered().style(
            boost::program_options::command_line_style::default_style |
            boost::program_options::command_line_style::allow_slash_for_short);

        boost::program_options::parsed_options parsed_options = parser.run();

        boost::program_options::variables_map vm;
        boost::program_options::store(parsed_options, vm);
        boost::program_options::notify(vm);

        if (vm.count("help"))
            std::cout << desc << '\n';
        else if (vm.count("age"))
            std::cout << "Age: " << age << '\n';
        else if (vm.count("phone"))
            to_cout(vm["phone"].as<std::vector<std::string>>());
        else if (vm.count("unreg"))
            to_cout(boost::program_options::collect_unrecognized(parsed_options.options,
                boost::program_options::exclude_positional));
        else if (vm.count("pi"))
            std::cout << "Pi: " << vm["pi"].as<float>() << '\n';
    }
    catch (const boost::program_options::error& ex)
    {
        std::cerr << ex.what() << '\n';
    }

    /*std::cout << "\n\n\n";
    return 0;*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
