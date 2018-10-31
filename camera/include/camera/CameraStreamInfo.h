/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_HARDWARE_CAMERASTREAMINFO_H
#define ANDROID_HARDWARE_CAMERASTREAMINFO_H

#include <utils/RefBase.h>
#include <utils/Vector.h>
#include <binder/Parcelable.h>
#include <gui/IGraphicBufferProducer.h>

namespace android {

class Surface;

namespace hardware {

struct CameraStreamInfo : public Parcelable {

    // those are needed so we can use a forward declaration of Surface, otherwise
    // the type is incomplete when the ctor/dtors are generated. This has the added
    // benefit that ctor/dtors are not inlined, which is good because they're not trivial
    // (because of the vtable.
    CameraStreamInfo();
    CameraStreamInfo(const CameraStreamInfo& rhs);
    CameraStreamInfo(CameraStreamInfo&& rhs) noexcept;
    virtual ~CameraStreamInfo();

    uint32_t                mWidth;
    uint32_t                mHeight;
    uint32_t                mFormat;
    sp<Surface>             mSurface;

    /**
     * Keep impl up-to-date with CameraStreamInfo.java in frameworks/base
     */
    status_t                readFromParcel(const android::Parcel* parcel) override;
    status_t                writeToParcel(android::Parcel* parcel) const override;
};

} // namespace hardware

struct CameraStreamInfo :
        public RefBase, public hardware::CameraStreamInfo {
  public:
    // Same as android::hardware::CameraStreamInfo, except that you can
    // put this in an sp<>
};

} // namespace android

#endif
