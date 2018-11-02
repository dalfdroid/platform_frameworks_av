/*
 * Copyright (C) 2015 The Android Open Source Project
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

package android.hardware;

import android.view.Surface;
import android.hardware.CameraStreamInfo;

/**
 * Binder interface for the camera service proxy running in system_server.
 *
 * Keep in sync with frameworks/av/include/camera/ICameraServiceProxy.h
 *
 * @hide
 */
interface ICameraServiceProxy
{
    /**
     * Ping the service proxy to update the valid users for the camera service.
     */
    oneway void pingForUserUpdate();

    /**
     * Values for notifyCameraState newCameraState
     */
    const int CAMERA_STATE_OPEN = 0;
    const int CAMERA_STATE_ACTIVE = 1;
    const int CAMERA_STATE_IDLE = 2;
    const int CAMERA_STATE_CLOSED = 3;

    /**
     * Values for notifyCameraState facing
     */
    const int CAMERA_FACING_BACK = 0;
    const int CAMERA_FACING_FRONT = 1;
    const int CAMERA_FACING_EXTERNAL = 2;

    /**
     * Update the status of a camera device.
     */
    oneway void notifyCameraState(String cameraId, int facing, int newCameraState,
            String clientName);

    /**
     * Report a new camera stream and possibly get a new rendering surface.
     * @param packageName The package for which this stream is being created.
     * @param CameraStreamInfo Information about the camera stream being created.
     * @return A new rendering surface target, if one exists, or null otherwise.
     */
    Surface reportCameraStream(String packageName, in CameraStreamInfo cameraStreamInfo);

    /**
     * Report that a camera stream is about to disconnect from its rendering
     * surface.
     * @param packageName The client package that created the camera stream.
     * @param CameraStreamInfo Information about the camera stream.
     */
    void reportSurfaceDisconnection(String packageName, in CameraStreamInfo cameraStreamInfo);
}
