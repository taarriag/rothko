// Copyright 2019, Cristián Donoso.
// This code has a BSD license. See LICENSE.

#pragma once

#include <stdint.h>

#include <utility>
#include <vector>

namespace rothko {

// WindowBackend
// =============================================================================
//
// Abstract interface each specific implementation of a window manager has to
// provide in order to work with Rothko. Each particular window manager (SDL,
// GLFW, etc.) must subclass this interface and suscribe a factory function
// keyed by it's particular entry into the WindowBackendType defined in
// rothko/window/common/window.h
//
// At the moment of needing a particular backend, the code will call that
// factory function to obtain an instance of that particular WindowBackend.
//
// It is recommended that the suscription is done at initialization time, so
// that the backend is assured to be there without any further work from part of
// the called.

enum class WindowEvent : uint32_t;

struct Input;
struct InitWindowConfig;
struct Window;

struct WindowBackend {
  virtual ~WindowBackend() = default;

  // Interface -----------------------------------------------------------------

  virtual bool Init(Window*, InitWindowConfig*) = 0;
  virtual void Shutdown() = 0;
  virtual std::vector<WindowEvent> NewFrame(Window*, Input*) = 0;

  // No-op if the window manager doesn't require it.
  virtual void SwapBuffers() {};

  // *** VULKAN SPECIFIC ***

  // These functions must be subclassed if needed. If a backend doesn't need
  // them, they can choose not to do so.
  // Calling them in a backend that doesn't support them will assert a failure.
  // (see window_backend.cc).

  // Instance extensions required by this window manager.
  virtual std::vector<const char*> GetVulkanInstanceExtensions();

  // |vk_instance| & |surface_khr| must be casted to the right type in the
  // implementation. This is so that we don't need to forward declare vulkan
  // typedefs.
  virtual bool CreateVulkanSurface(void* vk_instance, void* surface_khr);
};

}  // namespace rothko
