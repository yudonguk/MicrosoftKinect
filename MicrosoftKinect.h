#ifndef __MICROSOFT_KINECT_H__
#define __MICROSOFT_KINECT_H__

#include <windows.h>
#include <NuiApi.h>
#include <OprosLock.h>

#include "Kinect.h"

class MicrosoftKinect : public Kinect
{
public:
	MicrosoftKinect();
	virtual ~MicrosoftKinect();

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

public:
	int SetCameraAngle(float degree);
	int GetCameraAngle(float& degree);
	int GetSkeleton(vector<Skeleton>& output);
	int GetSkeleton(Skeleton& output, unsigned long id);
	int GetSkeletonID(vector<unsigned long>& output);
	int GetImage(ImageFrame& image);
	int GetDepthImage(DepthFrame& depth);

private:
	bool SetKinectProfile(Property& property);
	void TransformSkeletonToDepthImage(Position& result, const Vector4& skeletonPosition);
	bool GetSKeletonNextFrame();
	void ConvertNuiDepthToDepth(vector<uint16_t>& output, USHORT* pNuiDepth, const size_t maxCount);
	void ConvertNuiDepthToDepthUsingSSE(vector<uint16_t>& output, USHORT* pNuiDepth, const size_t maxCount);
	void InitDepthConverter();

private:
	void (MicrosoftKinect::*depthConverter)(vector<uint16_t>& output, USHORT* pNuiDepth, const size_t maxCount);

	OprosLock mLockSkeletonList;
	vector<Skeleton> mSkeletonList;

	INuiSensor* mpNuiSensor;

	HANDLE mHandleDepthStream;
	HANDLE mHandleColorStream;

	NUI_IMAGE_RESOLUTION mNuiColorResoultion;
	NUI_IMAGE_RESOLUTION mNuiDepthResoultion;
	bool mIsNearMode;
	bool mIsSkeletonTrackingMode;

	int mNuiIndex;

	OprosLock mLockTempImageFrame;
	ImageFrame mTempImageFrame;

	OprosLock mLockTempDepthFrame;
	DepthFrame mTempDepthFrame;
};

#endif