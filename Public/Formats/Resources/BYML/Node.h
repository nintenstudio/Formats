#pragma once

#include <Formats/IO/Stream.h>
#include <yaml-cpp/yaml.h>

namespace Formats::Resources::BYML {
	class Node {
	public:
		virtual bool Parse(Formats::IO::Stream& bStream) = 0;
		virtual bool Serialize(Formats::IO::Stream& bStream) = 0;

		virtual void EmitYAML(YAML::Emitter& out) = 0;
		virtual bool LoadYAML(YAML::Node& node) = 0;
	};
}