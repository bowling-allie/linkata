#ifndef LINKATA_SRC_LK_UTIL_HPP_
#define LINKATA_SRC_LK_UTIL_HPP_
#pragma once

#include <lk/lk.hpp>
#include <lk/resource.hpp>
#include <lk/ready_task_queue.hpp>

//#include <future>
#include <string>

#include <Corrade/Containers/Containers.h>
#include <Corrade/PluginManager/PluginManager.h>

#include <Magnum/GL/GL.h>
#include <Magnum/Trade/Trade.h>

namespace lk::util {
  Corrade::PluginManager::Manager<Magnum::Trade::AbstractImporter> &getImporterPluginManager();
  Corrade::PluginManager::Manager<Magnum::Trade::AbstractImageConverter> &getImageConverterPluginManager();

  Magnum::Trade::AbstractImageConverter *getImageConverter();
  Magnum::Trade::AbstractImporter *getImageImporter();

  Corrade::Containers::Optional<Magnum::Trade::ImageData2D>
  importImageData2D(Corrade::Containers::ArrayView<const char> data_);

  Corrade::Containers::Optional<Magnum::GL::BufferImage2D>
  createBufferImage2DFromImage(const Magnum::Trade::ImageData2D &image_, Magnum::GL::BufferUsage usage_);

  Corrade::Containers::Optional<Magnum::GL::Texture2D>
  createTexture2DFromImageData2D(const Magnum::Trade::ImageData2D &image_);

  Corrade::Containers::Optional<Magnum::GL::Texture2D>
  createSvgHandleFromData(Corrade::Containers::ArrayView<const char> data_);
/*
  Corrade::Containers::Optional<Magnum::GL::Texture2D>
  rasterizeSvg(
      std::string svg_data,
      int width,
      int height,
      Corrade::Containers::Optional<GLuint> existing_texture_id = {}
  );*/

  void setResDir(std::string dir_);
  std::string getResDir();
}

#endif //LINKATA_SRC_LK_UTIL_HPP_
