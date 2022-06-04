#include "controller.hxx"


int
main()
{
    int level = 0;
    std::cout << "What level do you want to start on? (0,1, or 2)\n";
    std::cin >> level;

    Model::set_round_num(level);

    Controller().run();

    return 0;
}
