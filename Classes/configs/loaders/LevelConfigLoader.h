#ifndef QIPAI_CONFIGS_LOADERS_LEVEL_CONFIG_LOADER_H
#define QIPAI_CONFIGS_LOADERS_LEVEL_CONFIG_LOADER_H

#include <string>
#include "configs/models/LevelConfig.h"

namespace qipai {

/**
 * @brief 关卡配置加载器。
 *
 * 从 JSON 文件加载关卡配置并解析为 LevelConfig。
 */
class LevelConfigLoader {
public:
    /**
     * @brief 从文件加载关卡配置。
     * @param filePath 配置文件路径。
     * @param outConfig 解析成功时写入的配置对象。
     * @param outError 解析失败时返回错误信息，可为空。
     * @return 是否加载成功。
     */
    static bool loadLevelConfig(
        const std::string& filePath,
        LevelConfig& outConfig,
        std::string* outError = nullptr);
};

} // namespace qipai

#endif // QIPAI_CONFIGS_LOADERS_LEVEL_CONFIG_LOADER_H
