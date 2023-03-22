/*
 * @Author: likecanyon 1174578375@qq.com
 * @Date: 2022-05-12 17:15:51
 * @LastEditors: likecanyon 1174578375@qq.com
 * @LastEditTime: 2023-03-22 16:19:47
 * @FilePath: /ur_rtde/examples/cpp/move_until_contact.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <cstdio>
#include <csignal>
#include <csignal>
using namespace ur_rtde;

RTDEControlInterface rtde_control("192.168.3.101");
RTDEReceiveInterface rtde_receive("192.168.3.101");

/// \brief 处理终端的Ctrl-C信号
/// \param signo
void signalHandler(int signo)
{
    if (signo == SIGINT)
    {
        // rtde_control.stopJ();
        rtde_control.stopL(30.0);

        //  rtde_control.stopScript();
        std::cout << "stop" << std::endl;
        exit(0);
    }
}

int main(int argc, char *argv[])
{

    if (signal(SIGINT, signalHandler) == SIG_ERR)
    {
        std::cout << "error" << std::endl;
        exit(0);
    }

    // // Parameters
    // std::vector<double> speed = {0, 0, -0.100, 0, 0, 0};
    // rtde_control.moveUntilContact(speed);
    // std::vector<double> TCPForce(6, 0.0);
    // TCPForce = rtde_receive.getActualTCPForce();
    // std::cout << "the TCPForce is: " << TCPForce[0] << " " << TCPForce[1] << " " << TCPForce[2] << " " << TCPForce[3]
    //           << " " << TCPForce[4] << " " << TCPForce[5] << std::endl;
    // rtde_control.zeroFtSensor();
    // std::cout << "the TCPForce is: " << TCPForce[0] << " " << TCPForce[1] << " " << TCPForce[2] << " " << TCPForce[3]
    //           << " " << TCPForce[4] << " " << TCPForce[5] << std::endl;
    std::vector<double> TCPPose = {0, 0, 0, 0, 0, 0};
    TCPPose = rtde_receive.getActualTCPPose();

    // TCPPose[2] = TCPPose[2] + 0.1;
    // rtde_control.moveL(TCPPose, 0.2);

    TCPPose[2] = TCPPose[2] - 0.1;
    rtde_control.moveL(TCPPose, 0.1);

    std::cout << "finish" << std::endl;

    rtde_control.stopScript();
    return 0;
}
