/*
**
** Copyright 2013, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#include <utils/Log.h>

#include <camera/CameraStreamInfo.h>

#include <binder/Parcel.h>
#include <gui/Surface.h>
#include <gui/view/Surface.h>

namespace android {
namespace hardware {

// These must be in the .cpp (to avoid inlining)
CameraStreamInfo::CameraStreamInfo() = default;
CameraStreamInfo::~CameraStreamInfo() = default;
CameraStreamInfo::CameraStreamInfo(const CameraStreamInfo& rhs) = default;
CameraStreamInfo::CameraStreamInfo(CameraStreamInfo&& rhs) noexcept = default;

status_t CameraStreamInfo::readFromParcel(const android::Parcel* parcel) {
    if (parcel == NULL) {
        ALOGE("%s: Null parcel", __FUNCTION__);
        return BAD_VALUE;
    }

    status_t err = OK;


    if ((err = parcel->readUint32(&mStreamId)) != OK) {
        ALOGE("%s: Failed to read stream id from parcel: %s (%d)",
              __FUNCTION__, strerror(-err), err);
        return err;
    }

    if ((err = parcel->readUint32(&mWidth)) != OK) {
        ALOGE("%s: Failed to read width from parcel: %s (%d)",
              __FUNCTION__, strerror(-err), err);
        return err;
    }

    if ((err = parcel->readUint32(&mHeight)) != OK) {
        ALOGE("%s: Failed to read height from parcel: %s (%d)",
              __FUNCTION__, strerror(-err), err);
        return err;
    }

    if ((err = parcel->readUint32(&mFormat)) != OK) {
        ALOGE("%s: Failed to read format from parcel: %s (%d)",
              __FUNCTION__, strerror(-err), err);
        return err;
    }

    view::Surface surfaceShim;
    if ((err = surfaceShim.readFromParcel(parcel)) != OK) {
        ALOGE("%s: Failed to read output target Surface from parcel: %s (%d)",
              __FUNCTION__, strerror(-err), err);
        return err;
    }

    sp<Surface> surface;
    if (surfaceShim.graphicBufferProducer != NULL) {
        surface = new Surface(surfaceShim.graphicBufferProducer);
    }
    mSurface = surface;

    return OK;
}

status_t CameraStreamInfo::writeToParcel(android::Parcel* parcel) const {
    if (parcel == NULL) {
        ALOGE("%s: Null parcel", __FUNCTION__);
        return BAD_VALUE;
    }

    status_t err = OK;

    parcel->writeUint32(mStreamId);
    parcel->writeUint32(mWidth);
    parcel->writeUint32(mHeight);
    parcel->writeUint32(mFormat);

    // Surface.writeToParcel
    view::Surface surfaceShim;
    surfaceShim.name = String16("unknown_name");
    surfaceShim.graphicBufferProducer = mSurface->getIGraphicBufferProducer();
    if ((err = surfaceShim.writeToParcel(parcel)) != OK) {
        ALOGE("%s: Failed to write output target Surface to parcel: %s (%d)",
              __FUNCTION__, strerror(-err), err);
        return err;
    }

    return OK;
}

} // namespace hardware
} // namespace android
