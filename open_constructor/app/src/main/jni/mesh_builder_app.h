#ifndef MESH_BUILDER_APP_H
#define MESH_BUILDER_APP_H

#include <jni.h>
#include <mutex>
#include <string>

#include "tango/scan.h"
#include "tango/service.h"
#include "scene.h"

namespace oc {

    class MeshBuilderApp {
    public:
        MeshBuilderApp();
        void OnCreate(JNIEnv *env, jobject caller_activity);
        void OnPause();
        void OnTangoServiceConnected(JNIEnv *env, jobject binder, double res, double dmin, double dmax,
                                     int noise, bool land, std::string dataset);
        void onPointCloudAvailable(TangoPointCloud *point_cloud);
        void onFrameAvailable(TangoCameraId id, const TangoImageBuffer *buffer);
        void OnSurfaceCreated();
        void OnSurfaceChanged(int width, int height);
        void OnDrawFrame();
        void OnToggleButtonClicked(bool t3dr_is_running);
        void OnClearButtonClicked();
        void Load(std::string filename);
        void Save(std::string filename, std::string dataset);
        void Texturize(std::string filename, std::string dataset);
        float CenterOfStaticModel(bool horizontal);
        void SetView(float p, float y, float mx, float my, bool g) { pitch = p; yaw = y; gyro = g;
                                                                            movex = mx; movey = my;}
        void SetZoom(float value) { zoom = value; }

    private:
        void DeleteResources();
        std::string GetFileName(int index, std::string extension);

        bool t3dr_is_running_;
        glm::mat4 image_matrix;
        glm::quat image_rotation;
        std::mutex binder_mutex_;
        std::mutex render_mutex_;

        bool point_cloud_available_;
        TangoPointCloud* front_cloud_;
        glm::mat4 point_cloud_matrix_;

        Scene main_scene_;
        TangoScan scan;
        TangoService tango;

        int poses_;
        bool gyro;
        bool landscape;
        float movex;
        float movey;
        float pitch;
        float yaw;
        float zoom;
    };
}

#endif
