import os
from importlib.resources import path
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout

class BuildWithConan(ConanFile):
	settings = "os", "compiler", "build_type", "arch"
	requires = "gtest/cci.20210126", "benchmark/1.7.1"

	def layout(self):
		self.folders.root = "../build"
		self.folders.source = "."
		self.folders.build = "build"
		current_layout = cmake_layout(self)

	def source(self):
		cmake_file = load(self, "CMakeLists.txt")

	def generate(self):
		tc = CMakeToolchain(self)
		tc.variables["generator"] = "Ninja"
		tc.variables["CMAKE_MAKE_PROGRAM"] = "/usr/bin/ninja"
		tc.variables["CMAKE_INSTALL_PREFIX"] = self.package_folder
		tc.variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
		tc.variables["LLVM_USE_LINKER"] = "lld"
		tc.generate()
		deps = CMakeDeps(self)
		deps.generate()

	def build(self):
		cmake_file_path = os.path.join(self.source_folder, "CMakeLists.txt")
		cmake_file = load(self, cmake_file_path)
		cmake = CMake(self)
		cmake.configure()
		cmake.build(target="format_project")
		cmake.build(target="run_clang_tidy")
		cmake.build(target="run_cppcheck")
		cmake.build(target="run_tests")
		cmake.build()
		cmake.install()