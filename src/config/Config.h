#pragma once

#include <cstdint>

namespace map_demo::config {

// 小地图渲染配置
struct MiniMapConfig {
    // 小地图直径占窗口宽度的比例
    float sizeRatio = 1.0f / 6.0f;

    // 小地图显示的区块半径（以 chunk 为单位）
    int radiusChunks = 5;

    // 小地图距离窗口右侧的边距（像素）
    float marginRight = 20.0f;

    // 小地图距离窗口顶部的边距（像素）
    float marginTop = 20.0f;

    // 背景不透明度（0.0 ~ 1.0）
    float backgroundAlpha = 1.0f;

    // 背景颜色（RGBA）
    std::uint32_t backgroundColor = 0x000000FF; // 黑色不透明

    // 普通区块边界线颜色
    std::uint32_t chunkLineColor = 0x787878FF; // 灰色

    // 当前区块边界线颜色
    std::uint32_t currentChunkColor = 0x3AA0FFFF; // 青色

    // 小地图外边框颜色
    std::uint32_t borderColor = 0x505050FF; // 深灰色

    // 玩家箭头外轮廓颜色
    std::uint32_t playerArrowOutlineColor = 0x000000FF; // 黑色

    // 玩家箭头填充颜色
    std::uint32_t playerArrowFillColor = 0xDC3232FF; // 红色

    // 坐标文字颜色
    std::uint32_t coordTextColor = 0xFFFFFFFF; // 白色

    // 坐标文字阴影颜色
    std::uint32_t coordShadowColor = 0x000000C8; // 半透明黑色

    // 圆形背景分段数
    int circleSegments = 64;

    // 线条裁剪边距（像素），防止线宽溢出圆形
    float lineClipInset = 1.0f;

    // 线条宽度
    float lineThickness = 1.0f;

    // 外边框宽度
    float borderThickness = 2.0f;

    // 坐标文字与地图底部的间距
    float coordTextMargin = 8.0f;

    // 玩家箭头大小
    struct {
        float length      = 10.0f;
        float halfWidth   = 7.0f;
        float innerLength = 8.0f;
        float innerWidth  = 5.0f;
    } arrow{};
};

// 平滑相机配置
struct SmoothCameraConfig {
    // 弹簧强度
    float springStrength = 36.0f;

    // 阻尼系数
    float damping = 7.0f;

    // 最大 deltaTime（秒），防止卡顿导致抖动
    float maxDeltaTime = 0.1f;

    // 渲染 yaw 偏置（度），用于让小地图箭头朝上对应玩家实际朝向
    float renderYawOffset = 180.0f;
};

// 地形扫描与缓存配置
struct TerrainConfig {
    // 每帧最多扫描的 chunk 数量
    int scanMaxChunksPerFrame = 32;

    // 扫描半径（方块），实际会按 chunk 对齐
    int scanRadius = 128;

    // 是否启用地形渲染
    bool enable = true;

    // 同一个 chunk 两次扫描之间的最小帧间隔
    int rescanIntervalFrames = 120;

    // 是否启用磁盘缓存
    bool enableDiskCache = true;

    // 是否启用透明水效果（类似 BedrockMap）
    bool enableTransparentWater = true;

    // 每个维度的 cameraHeight（Y 坐标）
    struct {
        int overworld = 320; // 主世界
        int nether    = 127; // 地狱
        int end       = 256; // 末地
    } cameraHeight;

    // 阴影渲染配置
    struct {
        // 0 = 无阴影，1 = 简单高度图梯度阴影，2 = 阴影图 + 边缘 bevel
        int renderStyle = 2;

        // Style 1 阴影强度：100 表示无效果，>100 变亮/<100 变暗的幅度
        int shadowLevel = 130;

        // Style 2 上采样倍数（1~16）
        int renderScale = 2;

        // Style 2 阴影 PCF 柔化半径（0~8，0 为硬阴影）
        int pcfRadius = 1;

        // 是否启用透明水效果
        bool transparentWater = true;

        // 固定光源方向（方位角 315° 西北，天顶角 60°）
        float lightAzimuth = 315.0f;
        float lightZenith  = 60.0f;
    } shadow;

    // 颜色 JSON 文件路径（相对于 mod 目录）
    const char* blockColorPath = "resources/colors/block_color.json";
    const char* biomeColorPath = "resources/colors/biome_color.json";
};

// 总配置
struct Config {
    int version = 1;

    float fontSize = 18.0f;

    MiniMapConfig      miniMap;
    SmoothCameraConfig smoothCamera;
    TerrainConfig      terrain;
};

// 全局配置实例
inline Config& getConfig() {
    static Config config;
    return config;
}

} // namespace map_demo::config
