<!--
 * @Author: likecanyon 1174578375@qq.com
 * @Date: 2023-03-22 11:33:09
 * @LastEditors: likecanyon 1174578375@qq.com
 * @LastEditTime: 2023-03-22 11:38:52
 * @FilePath: /ur_mflee_ws/readme.md
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
-->
# test  MFLEE with UR

## wrench_pub node 
just publish the original data and filtered data of the sensor
topic name :
"OriginalWrenchData" "FilteredWrenchData"

## Build
```
catking build
```

## Usage
```
roscore
rosrun ur_mflee_force wrench_pub
```

## To be continued
