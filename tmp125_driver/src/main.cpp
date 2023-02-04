#include <iostream>
#include "tmp125_driver.hpp"
#include <vector>
using namespace tmp125;
int main()
{
    std::cout << "Hello, World" << std::endl;

    Tmp125Driver driver;

    std::vector<uint8_t> data_word_127{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}; // 127
    float f = driver.data_word_to_temp(data_word_127);
    std::cout << f << std::endl;

    // std::vector<uint8_t> v127{0, 1, 1, 1, 1, 1, 1, 1}; // 127
    // std::vector<uint8_t> v125{0, 1, 1, 1, 1, 1, 0, 1}; // 125
    // std::vector<uint8_t> v25{0, 0, 0, 1, 1, 0, 0, 1}; // 25
    // std::vector<uint8_t> v10{0, 0, 0, 0, 1, 0, 1, 0}; // 10
    // std::vector<uint8_t> v0{0, 0, 0, 0, 0, 0, 0, 0}; // 0
    // std::vector<uint8_t> vUK{1, 1, 1, 1, 1, 1, 1, 1, 1}; // 127
    // std::vector<uint8_t> v_25{1, 1, 1, 0 ,0, 1, 1, 1}; // -25

    
    // int8_t temp_int = 0;

    // if (v_25[0] == 1)
    // {
    //     // negative number - Not and add 1 to values
    //     // NOT
    //     for (int i = 0; i < v_25.size(); i++)
    //     {
    //         v_25[i] = (v_25[i] ? 0 : 1);
    //     }
    //     // Add 1
    //     for (int i = v_25.size() -1; i >= 0; i--)
    //     {
    //         if (v_25[i] == 1)
    //         {
    //             v_25[i] = 0;
    //         } else
    //         {
    //             v_25[i] = 1;
    //             break;
    //         }
    //     }

    // }

    // for (int i = 0; i < v127.size(); i++)
    // {
    //     temp_int |= (v127[i] << (8 - 1) - i);
    // }
    // std::cout << static_cast<int32_t>(temp_int) << std::endl;

    // temp_int = 0;

    // for (int i = 0; i < v125.size(); i++)
    // {
    //     temp_int |= (v125[i] << (8 - 1) - i);
    // }
    // std::cout << static_cast<int32_t>(temp_int) << std::endl;

    // temp_int = 0;

    // for (int i = 0; i < v25.size(); i++)
    // {
    //     temp_int |= (v25[i] << (8 - 1) - i);
    // }
    // std::cout << static_cast<int32_t>(temp_int) << std::endl;

    // temp_int = 0;

    // for (int i = 0; i < v10.size(); i++)
    // {
    //     temp_int |= (v10[i] << (8 - 1) - i);
    // }
    // std::cout << static_cast<int32_t>(temp_int) << std::endl;

    // temp_int = 0;

    // for (int i = 0; i < v0.size(); i++)
    // {
    //     temp_int |= (v0[i] << (8 - 1) - i);
    // }
    // std::cout << static_cast<int32_t>(temp_int) << std::endl;

    // temp_int = 0;

    // for (int i = 0; i < vUK.size(); i++)
    // {
    //     temp_int |= (vUK[i] << (8 - 1) - i);
    // }
    // std::cout << static_cast<int32_t>(temp_int) << std::endl;

    // temp_int = 0;

    // for (int i = 0; i < v_25.size(); i++)
    // {
    //     temp_int |= (v_25[i] << (8 - 1) - i);
    // }
    // std::cout << static_cast<int32_t>(temp_int) << std::endl;

    // temp_int = 0;




    // std::cout << "Last chance";





}