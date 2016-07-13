//
//  SCNCamera.h
//
//  Copyright (c) 2012-2016 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNCamera
 @abstract SCNCamera相当于一个可以被SCNNode连接的摄像机
 @discussion 一个带有摄像机的节点可以被当做一个观察3D场景的点
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNCamera : NSObject <SCNAnimatable, SCNTechniqueSupport, NSCopying, NSSecureCoding>

/*!
 @method camera
 @abstract 创建并返回一个camera实例
 */
+ (instancetype)camera;

/*!
 @property name
 @abstract 定义接收者的名字
 */
@property(nonatomic, copy, nullable) NSString *name;

/*!
 @property xFov 
 视角FOV是指镜头所能覆盖的范围，(物体超过这个角就不会被收在镜头里),一个摄像机镜头能涵盖多大范围的景物，通常以角度来表示，这个角度就叫镜头的视角FOV。
 @abstract 设置x轴方向的视角大小
 @discussion 当x轴视角和y轴视角都为NULL时，默认使用一个60度的y轴视角。当两者都被设置时，选择一个最适合渲染器的比率的角度。当只有一个视角被设置时就会使用那个视角。x轴视角默认为0。
 */
@property(nonatomic) double xFov;

/*!
 @property yFov
 @abstract 设置y轴方向的视角大小。
 @discussion 当x轴视角和y轴视角都为NULL时，默认使用一个60度的y轴视角。当两者都被设置时，选择一个最适合渲染器的比率的角度。当只有一个视角被设置时就会使用那个视角。x轴视角默认为0。
 */
@property(nonatomic) double yFov;

/*!
 @property zNear
 @abstract 设置距离接收者最近的距离。
 @discussion 最近的值确定了摄像头与可视表面之间的最小距离。如果表面太接近摄像头（小于最小距离），那么表面会夹在一起（破碎）。最近的值必须要不同于0。默认值为1。
 */
@property(nonatomic) double zNear;

/*!
 @property zFar
 @abstract 设置距离接收者最远的距离。
 @discussion 最近的值确定了摄像头与可视表面之间的最大距离。如果表面离摄像头太远（大于最大距离），那么表面会夹在一起（破碎）。默认值为100。
 */
@property(nonatomic) double zFar;

/*!
 @property automaticallyAdjustsZRange
 @abstract 设置是否要接受者自动调整zNear和zFar的值。默认是NO。
 @discussion 当被设置成YES的时候，在整个场景里的渲染时间内，近的和原的平面都会自动适配包含该区域的最小立方体（bounding box）。设置合适的zNear或者zFar会自动设置这个属性为NO
 */
@property(nonatomic) BOOL automaticallyAdjustsZRange NS_AVAILABLE(10_9, 8_0);

/*!
 @property usesOrthographicProjection
 @abstract 设置接受者是否使用正投影。默认为NO。
 */
@property(nonatomic) BOOL usesOrthographicProjection;

/*!
 @property orthographicScale
 @abstract 设置正投影比例（比例越大看起来越小）。默认为1。
 @discussion 这个属性设置了摄像机的可视面积的大小。这个属性仅当usesOrthographicProjection为YES时有效。
 */
@property(nonatomic) double orthographicScale NS_AVAILABLE(10_9, 8_0);

/*!
 @property projectionTransform
 @abstract 对整个屏幕上的物体进行投影变换（4x4矩阵）。
 */
@property(nonatomic) SCNMatrix4 projectionTransform;

/*!
 @functiongroup Depth of field
 */
/*!
 @property focalDistance
 @abstract Determines the receiver's focal distance. Animatable.
 @discussion When non zero, the focal distance determines how the camera focuses the objects in the 3d scene. Defaults to 10.0
 */
@property(nonatomic) CGFloat focalDistance NS_AVAILABLE(10_9, 8_0);

/*!
 @property focalSize
 @abstract Determines the receiver's focal size. Animatable.
 @discussion Determines the size of the area around focalDistance where the objects are in focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalSize NS_AVAILABLE(10_9, 8_0);

/*!
 @property focalBlurRadius
 @abstract Determines the receiver's focal radius. Animatable.
 @discussion Determines the maximum amount of blur for objects out of focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalBlurRadius NS_AVAILABLE(10_9, 8_0);

/*!
 @property aperture
 @abstract Determines the receiver's aperture. Animatable.
 @discussion Determines how fast the transition between in-focus and out-of-focus areas is. The greater the aperture is the faster the transition is. Defaults to 1/8.
 */
@property(nonatomic) CGFloat aperture NS_AVAILABLE(10_9, 8_0);

/*!
 @property motionBlurIntensity
 @abstract Determines the intensity of the motion blur. Animatable. Defaults to 0.
 @discussion An intensity of zero means no motion blur. The intensity should not exceeed 1.
 */
@property(nonatomic) CGFloat motionBlurIntensity NS_AVAILABLE(10_12, 10_0);

/*!
 @functiongroup High Dynamic Range
 */
/*!
 @property wantsHDR
 @abstract Determines if the receiver has a high dynamic range. Defaults to NO.
 */
@property(nonatomic) BOOL wantsHDR NS_AVAILABLE(10_12, 10_0);

/*!
 @property exposureOffset
 @abstract Determines the logarithimc exposure biasing, in EV. Defaults to 0.
 */
@property(nonatomic) CGFloat exposureOffset NS_AVAILABLE(10_12, 10_0);

/*!
 @property averageGray
 @abstract Determines the average gray level desired in the final image. Defaults to 0.18.
 */
@property(nonatomic) CGFloat averageGray NS_AVAILABLE(10_12, 10_0);

/*!
 @property whitePoint
 @abstract Determines the smallest luminance level that will be mapped to white in the final image. Defaults to 1.
 */
@property(nonatomic) CGFloat whitePoint NS_AVAILABLE(10_12, 10_0);

/*!
 @property wantsExposureAdaptation
 @abstract Determines if the receiver should simulate an eye and continuously adjust to luminance. Defaults to YES.
 */
@property(nonatomic) BOOL wantsExposureAdaptation NS_AVAILABLE(10_12, 10_0);

/*!
 @property exposureAdaptationBrighteningSpeedFactor
 @abstract Determines the exposure adaptation speed when going from bright areas to dark areas. Defaults to 0.4.
 */
@property(nonatomic) CGFloat exposureAdaptationBrighteningSpeedFactor NS_AVAILABLE(10_12, 10_0);

/*!
 @property exposureAdaptationBrighteningSpeedFactor
 @abstract Determines the exposure adaptation speed whien going from dark areas to bright areas. Defaults to 0.6.
 */
@property(nonatomic) CGFloat exposureAdaptationDarkeningSpeedFactor NS_AVAILABLE(10_12, 10_0);

/*!
 @property minimumExposure
 @abstract Determines the minimum exposure offset of the adaptation, in EV. Defaults to -15.
 */
@property(nonatomic) CGFloat minimumExposure NS_AVAILABLE(10_12, 10_0);

/*!
 @property maximumExposure
 @abstract Determines the maximum exposure offset of the adaptation, in EV. Defaults to -15.
 */
@property(nonatomic) CGFloat maximumExposure NS_AVAILABLE(10_12, 10_0);

/*!
 @property bloomThreshold
 @abstract Determines the luminance threshold for the bloom effect. Animatable. Defaults to 1.
 */
@property(nonatomic) CGFloat bloomThreshold NS_AVAILABLE(10_12, 10_0);

/*!
 @property bloomIntensity
 @abstract Determines the intensity of the bloom effect. Animatable. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat bloomIntensity NS_AVAILABLE(10_12, 10_0);

/*!
 @property bloomBlurRadius
 @abstract Determines the radius of the bloom effect in pixels. Animatable. Defaults to 4.
 */
@property(nonatomic) CGFloat bloomBlurRadius NS_AVAILABLE(10_12, 10_0);

/*!
 @property vignettingPower
 @abstract Controls the shape of the vignetting effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat vignettingPower NS_AVAILABLE(10_12, 10_0);

/*!
 @property vignettingIntensity
 @abstract Controls the intensity of the vignetting effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat vignettingIntensity NS_AVAILABLE(10_12, 10_0);

/*!
 @property colorFringeStrength
 @abstract Controls the strength of the color shift effect. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat colorFringeStrength NS_AVAILABLE(10_12, 10_0);

/*!
 @property colorFringeIntensity
 @abstract Controls the intensity of the color shift effect. Defaults to 1.
 */
@property(nonatomic) CGFloat colorFringeIntensity NS_AVAILABLE(10_12, 10_0);

/*!
 @property saturation
 @abstract Controls the overall saturation of the scene. Defaults to 1 (no effect).
 */
@property(nonatomic) CGFloat saturation NS_AVAILABLE(10_12, 10_0);

/*!
 @property contrast
 @abstract Controls the overall contrast of the scene. Defaults to 0 (no effect).
 */
@property(nonatomic) CGFloat contrast NS_AVAILABLE(10_12, 10_0);

/*!
 @property colorGrading
 @abstract Specifies a lookup texture to apply color grading. The contents must a 2D image representing `n` slices of a unit color cube texture, arranged in an horizontal row of `n` images. For instance, a color cube of dimension 16x16x16 should be provided as an image of size 256x16.
 */
@property(nonatomic, readonly) SCNMaterialProperty *colorGrading NS_AVAILABLE(10_12, 10_0);

/*!
 @property categoryBitMask
 @abstract Determines the node categories that are visible from the receiver. Defaults to all bits set.
 */
@property(nonatomic) NSUInteger categoryBitMask NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END
