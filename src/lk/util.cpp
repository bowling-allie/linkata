#include "util.hpp"

#include <Corrade/Containers/Optional.h>
#include <Corrade/Utility/Debug.h>
#include <Corrade/Utility/Directory.h>

#include <Magnum/GL/BufferImage.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/GL/PixelFormat.h>
#include <Magnum/ImageView.h>
#include <Magnum/Math/Functions.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/AbstractImageConverter.h>

#if defined(CORRADE_TARGET_EMSCRIPTEN)
#include <emscripten.h>
#endif

#include <utility>

Corrade::PluginManager::Manager<Magnum::Trade::AbstractImporter> &lk::util::getImporterPluginManager() {
  static Corrade::PluginManager::Manager<Magnum::Trade::AbstractImporter> importerPluginManager_{};
  return importerPluginManager_;
}

Corrade::PluginManager::Manager<Magnum::Trade::AbstractImageConverter> &lk::util::getImageConverterPluginManager() {
  static Corrade::PluginManager::Manager<Magnum::Trade::AbstractImageConverter> imageConverterPluginManager_{};
  return imageConverterPluginManager_;
}

Magnum::Trade::AbstractImporter *lk::util::getImageImporter() {
  static Corrade::Containers::Pointer<Magnum::Trade::AbstractImporter>
      imageImporter_ = getImporterPluginManager().loadAndInstantiate("AnyImageImporter");
  return imageImporter_.get();
}

Magnum::Trade::AbstractImageConverter *lk::util::getImageConverter() {
  static Corrade::Containers::Pointer<Magnum::Trade::AbstractImageConverter>
      imageConverter_ = getImageConverterPluginManager().loadAndInstantiate("AnyImageConverter");
  return imageConverter_.get();
}

Corrade::Containers::Optional<Magnum::Trade::ImageData2D>
lk::util::importImageData2D(Corrade::Containers::ArrayView<const char> data_) {
  getImageImporter()->openData(data_);

  auto image_ = getImageImporter()->image2D(0);
  if (!image_) {
    Magnum::Fatal{} << "Failed to load image";
    return {};
  }

  return {std::move(*image_)};
}

Corrade::Containers::Optional<Magnum::GL::BufferImage2D>
lk::util::createBufferImage2DFromImage(const Magnum::Trade::ImageData2D &image_, Magnum::GL::BufferUsage usage_) {
  Magnum::GL::TextureFormat format;
  if (image_.format() == Magnum::PixelFormat::RGBA8Unorm) {
    format = Magnum::GL::TextureFormat::RGBA8;
  } else {
    Magnum::Fatal{} << "Image has unsupported PixelFormat: \"" << image_.format() << "\"";
    return {};
  }

  Magnum::GL::BufferImage2D buffer_image_{
      image_.storage(),
      Magnum::GL::PixelFormat::RGBA,
      Magnum::GL::PixelType::UnsignedByte, image_.size(),
      image_.data(),
      usage_
  };

  return {std::move(buffer_image_)};
}

Corrade::Containers::Optional<Magnum::GL::Texture2D>
lk::util::createTexture2DFromImageData2D(const Magnum::Trade::ImageData2D &image_) {
  Magnum::GL::TextureFormat format;
  if (image_.format() == Magnum::PixelFormat::RGBA8Unorm) {
    format = Magnum::GL::TextureFormat::RGBA8;
  } else {
    Magnum::Fatal{} << "Image has unsupported PixelFormat: \"" << image_.format() << "\"";
    return {};
  }

  Magnum::GL::Texture2D texture_{};
  texture_
      .setStorage(Magnum::Math::log2(image_.size().max()) + 1, format, image_.size())
          // .setStorage(1, format, image_.size())
      .setSubImage(0, {}, image_)
      .generateMipmap();

  return {std::move(texture_)};
}

#if defined(CORRADE_TARGET_EMSCRIPTEN)
EM_JS(void, EM_JS_rasterizeSvg, (const char* svg_data, int width, int height, GLuint svg_texture_id), {
  console.log('svg_data - ' + UTF8ToString(svg_data));

  var svg_image = new Image(width, height);
  svg_image.src = 'data:image/svg+xml,' + escape(UTF8ToString(svg_data));

  _glBindTexture(GLctx.TEXTURE_2D, svg_texture_id);
  GLctx.texParameteri(GLctx.TEXTURE_2D, GLctx.TEXTURE_MAG_FILTER, GLctx.LINEAR);
  GLctx.texParameteri(GLctx.TEXTURE_2D, GLctx.TEXTURE_MIN_FILTER, GLctx.LINEAR);
  GLctx.texParameteri(GLctx.TEXTURE_2D, GLctx.TEXTURE_WRAP_S, GLctx.CLAMP_TO_EDGE);
  GLctx.texParameteri(GLctx.TEXTURE_2D, GLctx.TEXTURE_WRAP_T, GLctx.CLAMP_TO_EDGE);
  GLctx.texImage2D(
      GLctx.TEXTURE_2D,
      0,
      GLctx.RGBA,
      2,
      2,
      0,
      GLctx.RGBA,
      GLctx.UNSIGNED_BYTE,
      new Uint8Array([
          0, 0, 0, 255,
          255, 0, 255, 255,
          255, 0, 255, 255,
          0, 0, 0, 255,
      ])
  );

  svg_image.decode().then(() => {
      _glBindTexture(GLctx.TEXTURE_2D, svg_texture_id);
      GLctx.texParameteri(GLctx.TEXTURE_2D, GLctx.TEXTURE_MAG_FILTER, GLctx.LINEAR);
      GLctx.texParameteri(GLctx.TEXTURE_2D, GLctx.TEXTURE_MIN_FILTER, GLctx.LINEAR);
      GLctx.texParameteri(GLctx.TEXTURE_2D, GLctx.TEXTURE_WRAP_S, GLctx.CLAMP_TO_EDGE);
      GLctx.texParameteri(GLctx.TEXTURE_2D, GLctx.TEXTURE_WRAP_T, GLctx.CLAMP_TO_EDGE);
      GLctx.texImage2D(
          GLctx.TEXTURE_2D,
          0,
          GLctx.RGBA,
          GLctx.RGBA,
          GLctx.UNSIGNED_BYTE,
          svg_image
      );
  });
});
#endif

/*
Corrade::Containers::Optional<Magnum::GL::Texture2D> lk::util::rasterizeSvg(
    std::string svg_data,
    int width,
    int height,
    Corrade::Containers::Optional<GLuint> existing_texture_id
) {
  // todo: finish

#if defined(CORRADE_TARGET_EMSCRIPTEN)
  Corrade::Containers::Optional<Magnum::GL::Texture2D> created_texture;
  GLuint texture_id;

  if (existing_texture_id) {
    texture_id = *existing_texture_id;
  } else {
    created_texture = Magnum::GL::Texture2D{};
    texture_id = created_texture->id();
  }

  EM_JS_rasterizeSvg(svg_data.c_str(), width, height, texture_id);

  if (existing_texture_id) {
    return {};
  } else {
    return std::move(created_texture);
  }
#else
#error
  return {};
#endif
}
*/

namespace {
  std::string res_dir{"res"};
}

void lk::util::setResDir(std::string dir_) {
  namespace Directory = Corrade::Utility::Directory;
#if defined(LINKATA_EMBED_RESOURCES)
  res_dir = std::move(dir_);
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
  detail::res_dir = std::move(dir_);
#else
  res_dir = std::move(dir_);
#endif
#endif
}

std::string lk::util::getResDir() {
  namespace Directory = Corrade::Utility::Directory;
#if defined(LINKATA_EMBED_RESOURCES)
  return {};
#else
#if defined(CORRADE_TARGET_EMSCRIPTEN)
  return {};
#else
  return res_dir;
#endif
#endif
}
