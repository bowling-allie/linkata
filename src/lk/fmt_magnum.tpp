#include <fmt/format.h>

/// Magnum::Animation::Interpolation
/// Magnum::Animation::Extrapolation
#if 1
#include <Magnum/Animation/Interpolation.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Animation::Interpolation> {
 private:
  using type = Magnum::Animation::Interpolation;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::Animation::Extrapolation> {
 private:
  using type = Magnum::Animation::Extrapolation;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

#if 1
#include <Magnum/Animation/Player.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Animation::State> {
 private:
  using type = Magnum::Animation::State;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Array<Size, T>
/// Magnum::Array1D<T>
/// Magnum::Array2D<T>
/// Magnum::Array3D<T>
#if 1
#include <Magnum/Array.h>

template<Magnum::UnsignedInt Dimensions, typename T>
struct fmt::formatter<Magnum::Array<Dimensions, T>> {
 private:
  using type = Magnum::Array<Dimensions, T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    fmt::format_to(ctx.out(), "Array(");
    for (Magnum::UnsignedInt i = 0; i < Dimensions - 1; ++i) {
      fmt::format_to(ctx.out(), "{}, ", value[i]);
    }
    fmt::format_to(ctx.out(), "{})", value[Dimensions - 1]);
    return ctx.out();
  }
};

template<typename T>
struct fmt::formatter<Magnum::Array1D<T>> {
 private:
  using type = Magnum::Array1D<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Array({})", value[0]);
  }
};

template<typename T>
struct fmt::formatter<Magnum::Array2D<T>> {
 private:
  using type = Magnum::Array2D<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Array({}, {})", value[0], value[1]);
  }
};

template<typename T>
struct fmt::formatter<Magnum::Array3D<T>> {
 private:
  using type = Magnum::Array3D<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Array({}, {}, {})", value[0], value[1], value[2]);
  }
};
#endif

/// Magnum::Audio::ImporterFeature
#if 0
#include <Magnum/Audio/AbstractImporter.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Audio::ImporterFeature> {
 private:
  using type = Magnum::Audio::ImporterFeature;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Audio::BufferFormat
#if 1
#include <Magnum/Audio/BufferFormat.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Audio::BufferFormat> {
 private:
  using type = Magnum::Audio::BufferFormat;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Audio::Context::HrtfStatus
#if 1
#include <Magnum/Audio/Context.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Audio::Context::HrtfStatus> {
 private:
  using type = Magnum::Audio::Context::HrtfStatus;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Audio::Renderer::Error
/// Magnum::Audio::Renderer::DistanceModel
#if 1
#include <Magnum/Audio/Renderer.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Audio::Renderer::Error> {
 private:
  using type = Magnum::Audio::Renderer::Error;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::Audio::Renderer::DistanceModel> {
 private:
  using type = Magnum::Audio::Renderer::DistanceModel;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Audio::Source::State
/// Magnum::Audio::Source::Type
#if 1
#include <Magnum/Audio/Source.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Audio::Source::State> {
 private:
  using type = Magnum::Audio::Source::State;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::Audio::Source::Type> {
 private:
  using type = Magnum::Audio::Source::Type;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::InputFileCallbackPolicy
#if 1
#include <Magnum/FileCallback.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::InputFileCallbackPolicy> {
 private:
  using type = Magnum::InputFileCallbackPolicy;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::DynamicAttribute::Kind
/// Magnum::GL::DynamicAttribute::Components
/// Magnum::GL::DynamicAttribute::DataType
/// Magnum::GL::Implementation::SizedAttribute<1, 1>::Components
/// Magnum::GL::Implementation::SizedAttribute<1, 2>::Components
/// Magnum::GL::Implementation::SizedAttribute<1, 3>::Components
/// Magnum::GL::Implementation::SizedAttribute<1, 4>::Components
/// Magnum::GL::Implementation::SizedMatrixAttribute<2>::Components
/// Magnum::GL::Implementation::SizedMatrixAttribute<3>::Components
/// Magnum::GL::Implementation::SizedMatrixAttribute<4>::Components
/// Magnum::GL::Implementation::FloatAttribute::DataType
/// Magnum::GL::Implementation::IntAttribute::DataType
/// Magnum::GL::Implementation::DoubleAttribute::DataType
/// Magnum::GL::Implementation::Attribute<Magnum::Math::Vector<3, Magnum::Float>>::DataType
/// Magnum::GL::Implementation::Attribute<Magnum::Math::Vector<4, Magnum::Float>>::Components
/// Magnum::GL::Implementation::Attribute<Magnum::Math::Vector<4, Magnum::Float>>::DataType
#if 1
#include <Magnum/GL/Attribute.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::DynamicAttribute::Kind> {
 private:
  using type = Magnum::GL::DynamicAttribute::Kind;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::DynamicAttribute::Components> {
 private:
  using type = Magnum::GL::DynamicAttribute::Components;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::DynamicAttribute::DataType> {
 private:
  using type = Magnum::GL::DynamicAttribute::DataType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::SizedAttribute<1, 1>::Components> {
 private:
  using type = Magnum::GL::Implementation::SizedAttribute<1, 1>::Components;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::SizedAttribute<1, 2>::Components> {
 private:
  using type = Magnum::GL::Implementation::SizedAttribute<1, 2>::Components;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::SizedAttribute<1, 3>::Components> {
 private:
  using type = Magnum::GL::Implementation::SizedAttribute<1, 3>::Components;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::SizedAttribute<1, 4>::Components> {
 private:
  using type = Magnum::GL::Implementation::SizedAttribute<1, 4>::Components;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::SizedMatrixAttribute<2>::Components> {
 private:
  using type = Magnum::GL::Implementation::SizedMatrixAttribute<2>::Components;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::SizedMatrixAttribute<3>::Components> {
 private:
  using type = Magnum::GL::Implementation::SizedMatrixAttribute<3>::Components;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::SizedMatrixAttribute<4>::Components> {
 private:
  using type = Magnum::GL::Implementation::SizedMatrixAttribute<4>::Components;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::FloatAttribute::DataType> {
 private:
  using type = Magnum::GL::Implementation::FloatAttribute::DataType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::IntAttribute::DataType> {
 private:
  using type = Magnum::GL::Implementation::IntAttribute::DataType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

#if !defined(MAGNUM_TARGET_GLES)
template<>
struct fmt::formatter<Magnum::GL::Implementation::DoubleAttribute::DataType> {
 private:
  using type = Magnum::GL::Implementation::DoubleAttribute::DataType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

template<>
struct fmt::formatter<Magnum::GL::Implementation::Attribute<Magnum::Math::Vector<3, Magnum::Float>>::DataType> {
 private:
  using type = Magnum::GL::Implementation::Attribute<Magnum::Math::Vector<3, Magnum::Float>>::DataType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::Attribute<Magnum::Math::Vector<4, Magnum::Float>>::Components> {
 private:
  using type = Magnum::GL::Implementation::Attribute<Magnum::Math::Vector<4, Magnum::Float>>::Components;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Implementation::Attribute<Magnum::Math::Vector<4, Magnum::Float>>::DataType> {
 private:
  using type = Magnum::GL::Implementation::Attribute<Magnum::Math::Vector<4, Magnum::Float>>::DataType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::Buffer::TargetHint
/// Magnum::GL::Buffer::Target
#if 1
#include <Magnum/GL/Buffer.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::Buffer::TargetHint> {
 private:
  using type = Magnum::GL::Buffer::TargetHint;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Buffer::Target> {
 private:
  using type = Magnum::GL::Buffer::Target;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::Context::Flag
/// Magnum::GL::Context::DetectedDriver
#if 1
#include <Magnum/GL/Context.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

#if !defined(MAGNUM_TARGET_WEBGL)
template<>
struct fmt::formatter<Magnum::GL::Context::Flag> {
 private:
  using type = Magnum::GL::Context::Flag;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

template<>
struct fmt::formatter<Magnum::GL::Context::DetectedDriver> {
 private:
  using type = Magnum::GL::Context::DetectedDriver;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::DebugOutput::Source
/// Magnum::GL::DebugOutput::Type
/// Magnum::GL::DebugOutput::Severity
/// Magnum::GL::DebugMessage::Source
/// Magnum::GL::DebugMessage::Type
/// Magnum::GL::DebugGroup::Source
#if !defined(MAGNUM_TARGET_WEBGL)
#include <Magnum/GL/DebugOutput.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::DebugOutput::Source> {
 private:
  using type = Magnum::GL::DebugOutput::Source;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::DebugOutput::Type> {
 private:
  using type = Magnum::GL::DebugOutput::Type;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::DebugOutput::Severity> {
 private:
  using type = Magnum::GL::DebugOutput::Severity;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::DebugMessage::Source> {
 private:
  using type = Magnum::GL::DebugMessage::Source;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::DebugMessage::Type> {
 private:
  using type = Magnum::GL::DebugMessage::Type;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::DebugGroup::Source> {
 private:
  using type = Magnum::GL::DebugGroup::Source;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::DefaultFramebuffer::Status
#if 1
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::DefaultFramebuffer::Status> {
 private:
  using type = Magnum::GL::DefaultFramebuffer::Status;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::Framebuffer::Status
#if 1
#include <Magnum/GL/Framebuffer.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::Framebuffer::Status> {
 private:
  using type = Magnum::GL::Framebuffer::Status;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::MeshPrimitive
/// Magnum::GL::MeshIndexType
#if 1
#include <Magnum/GL/Mesh.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::MeshPrimitive> {
 private:
  using type = Magnum::GL::MeshPrimitive;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::MeshIndexType> {
 private:
  using type = Magnum::GL::MeshIndexType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::PixelFormat
/// Magnum::GL::PixelType
/// Magnum::GL::CompressedPixelFormat
#if 1
#include <Magnum/GL/PixelFormat.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::PixelFormat> {
 private:
  using type = Magnum::GL::PixelFormat;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::PixelType> {
 private:
  using type = Magnum::GL::PixelType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::CompressedPixelFormat> {
 private:
  using type = Magnum::GL::CompressedPixelFormat;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::Renderer::Error
/// Magnum::GL::Renderer::ResetNotificationStrategy
/// Magnum::GL::Renderer::GraphicsResetStatus
#if 1
#include <Magnum/GL/Renderer.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::Renderer::Error> {
 private:
  using type = Magnum::GL::Renderer::Error;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

#if !defined(MAGNUM_TARGET_WEBGL)
template<>
struct fmt::formatter<Magnum::GL::Renderer::ResetNotificationStrategy> {
 private:
  using type = Magnum::GL::Renderer::ResetNotificationStrategy;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::Renderer::GraphicsResetStatus> {
 private:
  using type = Magnum::GL::Renderer::GraphicsResetStatus;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif
#endif

/// Magnum::GL::SamplerFilter
/// Magnum::GL::SamplerMipmap
/// Magnum::GL::SamplerWrapping
/// Magnum::GL::SamplerCompareMode
/// Magnum::GL::SamplerCompareFunction
/// Magnum::GL::SamplerDepthStencilMode
#if 1
#include <Magnum/GL/Sampler.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::SamplerFilter> {
 private:
  using type = Magnum::GL::SamplerFilter;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::SamplerMipmap> {
 private:
  using type = Magnum::GL::SamplerMipmap;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::SamplerWrapping> {
 private:
  using type = Magnum::GL::SamplerWrapping;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::SamplerCompareMode> {
 private:
  using type = Magnum::GL::SamplerCompareMode;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::GL::SamplerCompareFunction> {
 private:
  using type = Magnum::GL::SamplerCompareFunction;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

#if !defined(MAGNUM_TARGET_GLES2) && !defined(MAGNUM_TARGET_WEBGL)
template<>
struct fmt::formatter<Magnum::GL::SamplerDepthStencilMode> {
 private:
  using type = Magnum::GL::SamplerDepthStencilMode;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif
#endif

/// Magnum::GL::Shader::Type
#if 1
#include <Magnum/GL/Shader.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::Shader::Type> {
 private:
  using type = Magnum::GL::Shader::Type;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::TextureFormat
#if 1
#include <Magnum/GL/TextureFormat.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::TextureFormat> {
 private:
  using type = Magnum::GL::TextureFormat;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::GL::Version
#if 1
#include <Magnum/GL/Version.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::GL::Version> {
 private:
  using type = Magnum::GL::Version;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Math::Unit<Magnum::Math::Rad, T>
/// Magnum::Math::Unit<Magnum::Math::Deg, T>
#if 1
#include <Magnum/Math/Angle.h>

template<typename T>
struct fmt::formatter<Magnum::Math::Unit<Magnum::Math::Rad, T>> {
 private:
  using type = Magnum::Math::Unit<Magnum::Math::Rad, T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Rad({})", static_cast<T>(value));
  }
};

template<typename T>
struct fmt::formatter<Magnum::Math::Unit<Magnum::Math::Deg, T>> {
 private:
  using type = Magnum::Math::Unit<Magnum::Math::Deg, T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Deg({})", static_cast<T>(value));
  }
};
#endif

/// Magnum::Math::Bezier<Order, Dimensions, T>
#if 1
#include <Magnum/Math/Bezier.h>

template<Magnum::UnsignedInt Order, Magnum::UnsignedInt Dimensions, typename T>
struct fmt::formatter<Magnum::Math::Bezier<Order, Dimensions, T>> {
 private:
  using type = Magnum::Math::Bezier<Order, Dimensions, T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    fmt::format_to(ctx.out(), "Bezier(");
    for(std::size_t i = 0; i != Order; ++i) {
      fmt::format_to(ctx.out(), "{{");
      for(std::size_t j = 0; j < Dimensions - 1; ++j) {
        fmt::format_to(ctx.out(), "{}, ", value[i][j]);
      }
      fmt::format_to(ctx.out(), "{}}}, ", value[i][Dimensions - 1]);
    }

    fmt::format_to(ctx.out(), "{{");
    for(std::size_t i = 0; i < Dimensions - 1; ++i) {
      fmt::format_to(ctx.out(), "{}, ", value[Order][i]);
    }
    return fmt::format_to(ctx.out(), "{}}})", value[Order][Dimensions - 1]);
  }
};
#endif

/// Magnum::Math::BoolVector<Size>
#if 1
#include <Magnum/Math/BoolVector.h>

template<std::size_t Size>
struct fmt::formatter<Magnum::Math::BoolVector<Size>> {
 private:
  using type = Magnum::Math::BoolVector<Size>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    fmt::format_to(ctx.out(), "BoolVector(");
    for (std::size_t i = 0; i < type::DataSize - 1; ++i) {
      fmt::format_to(ctx.out(), "0b{:b}, ", value.data()[i]);
    }

    constexpr bool mod8 = Size % 8 == 0;
    const auto last_data_ = value.data()[type::DataSize - 1];
    if constexpr (mod8) {
      fmt::format_to(ctx.out(), "0b{:b})", last_data_);
    } else {
      fmt::format_to(ctx.out(), "0b");
      constexpr int EndSize = ((Size - 1) % 8) + 1;
      {
        std::size_t i = EndSize;
        while (true) {
          --i;
          fmt::format_to(ctx.out(), "{}", (last_data_ >> (i % 8)) & 0x01);
          if (i == 0) break;
        }
      }
      fmt::format_to(ctx.out(), ")", value.data()[type::DataSize - 1], EndSize);
    }

    return ctx.out();
  }
};
#endif

/// Magnum::Math::ColorHsv<T>
/// Magnum::Math::Color3<T>
/// Magnum::Math::Color4<T>
#if 1
#include <Magnum/Math/Color.h>

template<typename T>
struct fmt::formatter<Magnum::Math::ColorHsv<T>> {
 private:
  using type = Magnum::Math::ColorHsv<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "ColorHsv({}, {}, {})", value.hue, value.saturation, value.value);
  }
};

template<typename T>
struct fmt::formatter<Magnum::Math::Color3<T>> {
 private:
  using type = Magnum::Math::Color3<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "#{:x}{:x}{:x}", value.r(), value.g(), value.b());
  }
};

template<typename T>
struct fmt::formatter<Magnum::Math::Color4<T>> {
 private:
  using type = Magnum::Math::Color4<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "#{:x}{:x}{:x}{:x}", value.r(), value.g(), value.b(), value.a());
  }
};
#endif

/// Magnum::Math::Complex<T>
#if 1
#include <Magnum/Math/Complex.h>

template<typename T>
struct fmt::formatter<Magnum::Math::Complex<T>> {
 private:
  using type = Magnum::Math::Complex<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Complex({}, {})", value.real(), value.imaginary());
  }
};
#endif

/// Magnum::Math::CubicHermite<T>
#if 1
#include <Magnum/Math/CubicHermite.h>

template<typename T>
struct fmt::formatter<Magnum::Math::CubicHermite<T>> {
 private:
  using type = Magnum::Math::CubicHermite<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "CubicHermite({}, {}, {})", value.inTangent(), value.point(), value.outTangent());
  }
};
#endif

/// Magnum::Math::Dual<T>
#if 1
#include <Magnum/Math/Dual.h>

template<typename T>
struct fmt::formatter<Magnum::Math::Dual<T>> {
 private:
  using type = Magnum::Math::Dual<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Dual({}, {})", value.real(), value.dual());
  }
};
#endif

/// Magnum::Math::DualComplex<T>
#if 1
#include <Magnum/Math/DualComplex.h>

template<typename T>
struct fmt::formatter<Magnum::Math::DualComplex<T>> {
 private:
  using type = Magnum::Math::DualComplex<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(
        ctx.out(),
        "DualComplex({{{}, {}}}, {{{}, {}}})",
        value.real().real(),
        value.real().imaginary(),
        value.dual().real(),
        value.dual().imaginary()
    );
  }
};
#endif

/// Magnum::Math::DualQuaternion<T>
#if 1
#include <Magnum/Math/DualQuaternion.h>

template<typename T>
struct fmt::formatter<Magnum::Math::DualQuaternion<T>> {
 private:
  using type = Magnum::Math::DualQuaternion<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(
        ctx.out(),
        "DualQuaternion({{{{{}, {}, {}}}, {}}}, {{{{{}, {}, {}}}, {}}})",
        value.real().vector().x(),
        value.real().vector().x(),
        value.real().vector().x(),
        value.real().scalar(),
        value.dual().vector().x(),
        value.dual().vector().x(),
        value.dual().vector().x(),
        value.dual().scalar()
    );
  }
};
#endif

/// Magnum::Math::Frustum<T>
#if 1
#include <Magnum/Math/Frustum.h>

template<typename T>
struct fmt::formatter<Magnum::Math::Frustum<T>> {
 private:
  using type = Magnum::Math::Frustum<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(
        ctx.out(),
        "DualQuaternion({{{{{}, {}, {}}}, {}}}, {{{{{}, {}, {}}}, {}}})",
        value.real().vector().x(),
        value.real().vector().x(),
        value.real().vector().x(),
        value.real().scalar(),
        value.dual().vector().x(),
        value.dual().vector().x(),
        value.dual().vector().x(),
        value.dual().scalar()
    );
  }
};
#endif

/// Magnum::Math::Half
#if 1
#include <Magnum/Math/Half.h>

template<>
struct fmt::formatter<Magnum::Math::Half> {
 private:
  using type = Magnum::Math::Half;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(),"{:.4}", static_cast<Magnum::Float>(value));
  }
};
#endif

/// Magnum::Math::Quaternion<T>
#if 1
#include <Magnum/Math/Quaternion.h>

template<typename T>
struct fmt::formatter<Magnum::Math::Quaternion<T>> {
 private:
  using type = Magnum::Math::Quaternion<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(
        ctx.out(),
        "Quaternion({{{}, {}, {}}}, {})",
        value.vector().x(),
        value.vector().y(),
        value.vector().z(),
        value.scalar()
    );
  }
};
#endif

/// Magnum::Math::Range<Dimensions, T>
#if 1
#include <Magnum/Math/Range.h>

template<Magnum::UnsignedInt Dimensions,  typename T>
struct fmt::formatter<Magnum::Math::Range<Dimensions, T>> {
 private:
  using type = Magnum::Math::Range<Dimensions, T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    if constexpr (Dimensions > 1) {
      fmt::format_to(ctx.out(),"Range({{");
      for(std::size_t i = 0; i < Dimensions - 1; ++i) {
        fmt::format_to(ctx.out(), "{}, ", value.min()[i]);
      }
      fmt::format_to(ctx.out(),"{}}}, {{", value.min()[Dimensions - 1]);
      for (std::size_t i = 0; i < Dimensions - 1; ++i) {
        fmt::format_to(ctx.out(), "{}, ", value.max()[i]);
      }
      fmt::format_to(ctx.out(), "{}}})", value.max()[Dimensions - 1]);
    } else {
      fmt::format_to(ctx.out(),"Range({{{}}}, {{{}}})", value.min(), value.max());
    }
    return ctx.out();
  }
};
#endif

/// Magnum::Math::RectangularMatrix<Columns, Rows, T>
#if 1
#include <Magnum/Math/RectangularMatrix.h>

template<std::size_t Columns, std::size_t Rows, typename T>
struct fmt::formatter<Magnum::Math::RectangularMatrix<Columns, Rows, T>> {
 private:
  using type = Magnum::Math::RectangularMatrix<Columns, Rows, T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    fmt::format_to(ctx.out(),"Matrix(");
    for(std::size_t i = 0; i < Rows - 1; ++i) {
      for (std::size_t j = 0; j < Columns - 1; ++j) {
        fmt::format_to(ctx.out(), "{}, ", value[j][i]);
      }
      fmt::format_to(ctx.out(), "{},\n      ", value[Columns - 1][i]);
    }
    for (std::size_t i = 0; i < Columns - 1; ++i) {
      fmt::format_to(ctx.out(), "{}, ", value[i][Rows - 1]);
    }
    return fmt::format_to(ctx.out(), "{})", value[Columns - 1][Rows - 1]);
  }
};
#endif

/// Magnum::Math::Vector<Size, T>
#if 1
#include <Magnum/Math/Vector.h>

template<std::size_t Size, typename T>
struct fmt::formatter<Magnum::Math::Vector<Size, T>> {
 private:
  using type = Magnum::Math::Vector<Size, T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    fmt::format_to(ctx.out(), "Vector(");
    for (std::size_t i = 0; i < Size - 1; ++i) {
      fmt::format_to(ctx.out(), "{}, ", value[i]);
    }
    return fmt::format_to(ctx.out(), "{})", value[Size - 1]);
  }
};
#endif

/// Magnum::Math::Vector2<T>
#if 1
#include <Magnum/Math/Vector2.h>

template<typename T>
struct fmt::formatter<Magnum::Math::Vector2<T>> {
 private:
  using type = Magnum::Math::Vector2<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Vector({}, {})", value[0], value[1]);
  }
};
#endif

/// Magnum::Math::Vector3<T>
#if 1
#include <Magnum/Math/Vector3.h>

template<typename T>
struct fmt::formatter<Magnum::Math::Vector3<T>> {
 private:
  using type = Magnum::Math::Vector3<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Vector({}, {}, {})", value[0], value[1], value[2]);
  }
};
#endif

/// Magnum::Math::Vector4<T>
#if 1
#include <Magnum/Math/Vector4.h>

template<typename T>
struct fmt::formatter<Magnum::Math::Vector4<T>> {
 private:
  using type = Magnum::Math::Vector4<T>;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "Vector({}, {}, {}, {})", value[0], value[1], value[2], value[3]);
  }
};
#endif

/// Magnum::MeshPrimitive
/// Magnum::MeshIndexType
#if 1
#include <Magnum/Mesh.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::MeshPrimitive> {
 private:
  using type = Magnum::MeshPrimitive;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::MeshIndexType> {
 private:
  using type = Magnum::MeshIndexType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::PixelFormat
/// Magnum::CompressedPixelFormat
#if 1
#include <Magnum/PixelFormat.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::PixelFormat> {
 private:
  using type = Magnum::PixelFormat;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::CompressedPixelFormat> {
 private:
  using type = Magnum::CompressedPixelFormat;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::ResourceState
/// Magnum::ResourceKey
#if 1
#include <Magnum/Resource.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::ResourceState> {
 private:
  using type = Magnum::ResourceState;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::ResourceKey> {
 private:
  using type = Magnum::ResourceKey;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::SamplerFilter
/// Magnum::SamplerMipmap
/// Magnum::SamplerWrapping
#if 1
#include <Magnum/Sampler.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::SamplerFilter> {
 private:
  using type = Magnum::SamplerFilter;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::SamplerMipmap> {
 private:
  using type = Magnum::SamplerMipmap;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::SamplerWrapping> {
 private:
  using type = Magnum::SamplerWrapping;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::SceneGraph::AnimationState
#if 1
#include <Magnum/SceneGraph/Animable.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::SceneGraph::AnimationState> {
 private:
  using type = Magnum::SceneGraph::AnimationState;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Shaders::Implementation::FlatFlag
#if 1
#include <Magnum/Shaders/Flat.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Shaders::Implementation::FlatFlag> {
 private:
  using type = Magnum::Shaders::Implementation::FlatFlag;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Shaders::MeshVisualizer2D::Flag
/// Magnum::Shaders::MeshVisualizer3D::Flag
#if 1
#include <Magnum/Shaders/MeshVisualizer.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Shaders::MeshVisualizer2D::Flag> {
 private:
  using type = Magnum::Shaders::MeshVisualizer2D::Flag;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::Shaders::MeshVisualizer3D::Flag> {
 private:
  using type = Magnum::Shaders::MeshVisualizer3D::Flag;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Shaders::Phong::Flag
#if 1
#include <Magnum/Shaders/Phong.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Shaders::Phong::Flag> {
 private:
  using type = Magnum::Shaders::Phong::Flag;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Text::FontFeature
#if 1
#include <Magnum/Text/AbstractFont.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Text::FontFeature> {
 private:
  using type = Magnum::Text::FontFeature;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Text::FontConverterFeature
#if 1
#include <Magnum/Text/AbstractFontConverter.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Text::FontConverterFeature> {
 private:
  using type = Magnum::Text::FontConverterFeature;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Trade::ImageConverterFeature
#if 1
#include <Magnum/Trade/AbstractImageConverter.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Trade::ImageConverterFeature> {
 private:
  using type = Magnum::Trade::ImageConverterFeature;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Trade::ImporterFeature
#if 1
#include <Magnum/Trade/AbstractImporter.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Trade::ImporterFeature> {
 private:
  using type = Magnum::Trade::ImporterFeature;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Trade::MaterialType
/// Magnum::Trade::MaterialAlphaMode
/// Magnum::Trade::AbstractMaterialData::Flag
#if 1
#include <Magnum/Trade/AbstractMaterialData.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Trade::MaterialType> {
 private:
  using type = Magnum::Trade::MaterialType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::Trade::MaterialAlphaMode> {
 private:
  using type = Magnum::Trade::MaterialAlphaMode;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::Trade::AbstractMaterialData::Flag> {
 private:
  using type = Magnum::Trade::AbstractMaterialData::Flag;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Trade::AnimationTrackType
/// Magnum::Trade::AnimationTrackTargetType
#if 1
#include <Magnum/Trade/AnimationData.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Trade::AnimationTrackType> {
 private:
  using type = Magnum::Trade::AnimationTrackType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::Trade::AnimationTrackTargetType> {
 private:
  using type = Magnum::Trade::AnimationTrackTargetType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Trade::CameraType
#if 1
#include <Magnum/Trade/CameraData.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Trade::CameraType> {
 private:
  using type = Magnum::Trade::CameraType;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Trade::LightData::Type
#if 1
#include <Magnum/Trade/LightData.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Trade::LightData::Type> {
 private:
  using type = Magnum::Trade::LightData::Type;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Trade::ObjectInstanceType2D
/// Magnum::Trade::ObjectFlag2D
#if 1
#include <Magnum/Trade/ObjectData2D.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Trade::ObjectInstanceType2D> {
 private:
  using type = Magnum::Trade::ObjectInstanceType2D;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::Trade::ObjectFlag2D> {
 private:
  using type = Magnum::Trade::ObjectFlag2D;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Trade::ObjectInstanceType3D
/// Magnum::Trade::ObjectFlag3D
#if 1
#include <Magnum/Trade/ObjectData3D.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Trade::ObjectInstanceType3D> {
 private:
  using type = Magnum::Trade::ObjectInstanceType2D;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};

template<>
struct fmt::formatter<Magnum::Trade::ObjectFlag3D> {
 private:
  using type = Magnum::Trade::ObjectFlag3D;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Trade::PhongMaterialData::Flag
#if 1
#include <Magnum/Trade/PhongMaterialData.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Trade::PhongMaterialData::Flag> {
 private:
  using type = Magnum::Trade::PhongMaterialData::Flag;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif

/// Magnum::Trade::TextureData::Type
#if 1
#include <Magnum/Trade/TextureData.h>
#include <Corrade/Utility/Debug.h>
#include <sstream>

template<>
struct fmt::formatter<Magnum::Trade::TextureData::Type> {
 private:
  using type = Magnum::Trade::TextureData::Type;

 public:
  template<typename ParseContext>
  auto parse(ParseContext &ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const type &value, FormatContext &ctx) {
    std::ostringstream out;
    Corrade::Utility::Debug d{&out, Corrade::Utility::Debug::Flag::NoNewlineAtTheEnd};
    d << value;
    return fmt::format_to(ctx.out(), "{}", out.str());
  }
};
#endif
