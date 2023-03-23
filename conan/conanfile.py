from importlib.resources import path
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class BuildWithConan(ConanFile):
	settings = "os", "compiler", "build_type", "arch"
	requires = "gtest/cci.20210126", "benchmark/1.7.0"


	def generate(self):
		tc = CMakeToolchain(self)
		tc.variables["generator"] = "Ninja"
		tc.generate()
		deps = CMakeDeps(self)
		deps.generate()

	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build(target="format_project")
		cmake.build(target="run_clang_tidy")
		cmake.build(target="run_cppcheck")
		cmake.build(target="run_tests")
		cmake.build()
		cmake.install()