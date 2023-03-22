/*
 * @Author: likecanyon 1174578375@qq.com
 * @Date: 2022-05-12 17:15:51
 * @LastEditors: likecanyon 1174578375@qq.com
 * @LastEditTime: 2023-03-22 20:04:34
 * @FilePath: /ur_rtde/examples/cpp/move_until_contact.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <cstdio>
#include <csignal>
#include <csignal>
#include <thread>

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

void ur_move()
{
    std::vector<double> TCPPose = {0, 0, 0, 0, 0, 0};
    TCPPose = rtde_receive.getActualTCPPose();
    while (1)
    {
        TCPPose[2] = TCPPose[2] + 0.1;
        rtde_control.moveL(TCPPose, 0.2);

        TCPPose[2] = TCPPose[2] - 0.1;
        rtde_control.moveL(TCPPose, 0.1);
    }

    std::cout << "finish" << std::endl;
}

void ur_info()
{

    std::vector<double> TCPPose;
    int time_count = 0;
    while (time_count < 60 * 3)
    {
        TCPPose = rtde_receive.getActualTCPPose();
        std::this_thread::sleep_for(std::chrono::duration<double>(1));
        std::cout << TCPPose[0] << "\t" << TCPPose[1] << "\t" << TCPPose[2] << std::endl;
    }
}

int main(int argc, char *argv[])
{

    if (signal(SIGINT, signalHandler) == SIG_ERR)
    {
        std::cout << "error" << std::endl;
        exit(0);
    }

    std::vector<double> InitQ{0, -1.57, -1.57, -1.57, 1.57, 0};
    rtde_control.moveJ(InitQ);

    std::thread motion{&ur_move};
    std::thread info{&ur_info};

    motion.join();
    info.join();

    return 0;
}
