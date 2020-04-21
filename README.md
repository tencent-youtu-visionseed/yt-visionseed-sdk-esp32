### esp32-sdk for VisionSeed - a camera module with AI ability

[![License](https://img.shields.io/github/license/tencent-youtu-visionseed/yt-visionseed-sdk-esp32)](https://raw.githubusercontent.com/tencent-youtu-visionseed/yt-visionseed-sdk-esp32/master/LICENSE)

---

腾讯优图VisionSeed，是一个融AI算法+运算能力+摄像头为一体的硬件模组，致力于向硬件开发者提供世界领先的AI能力，通过VisionSeed可轻松使用优图人脸检测、识别、配准、姿态、属性等能力。

VisionSeed的开发团队觉得AI加上WiFi能够碰撞出有意思的火花，特意制作了这个SDK，通过UART接口，把结构化的AI分析结果，输出到ESP32，开发AI应用触手可及。

本SDK基于ESP-IDF的新一代build系统，在以下版本中通过过测试
Tested on ESP-IDF v3.2.2, xtensa-esp32-elf toolchain v5.2.0
VisionSeed固件版本 V1.2.3（请通过官网的VisionSeed配置工具升级固件）

# run example
```shell
git clone https://github.com/tencent-youtu-visionseed/yt-visionseed-sdk-esp32
cd yt-visionseed-sdk-esp32/example
idf.py flash monitor
```

# integrate into your project
esp32的sdk是以components的形式存在，建议通过git submodule，将yt-visionseed-sdk-esp32作为子模块放入您工程的components目录中

# more
Homepage: https://visionseed.youtu.qq.com

技术交流QQ群: 684338220(超多大佬)
