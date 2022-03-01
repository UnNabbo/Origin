#pragma once

#include "Origin/Core/Core.h"

#include "stdint.h"

namespace Origin {

	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Bool,
		Mat3, Mat4,
	};

	

	struct ORIGIN_API BufferElement {

		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;


		BufferElement(ShaderDataType type, std::string name, bool normalized = false)
			: Name(name), Type(type), Size(SizeOfShaderDataType(type)), Offset(0), Normalized(normalized){}

		
		uint32_t GetComponetCount() const {
			switch (Type) {
				case ShaderDataType::Bool:   return 1;
				case ShaderDataType::Int:    return 1;
				case ShaderDataType::Int2:   return 2;
				case ShaderDataType::Int3:   return 3;
				case ShaderDataType::Int4:   return 4;
				case ShaderDataType::Float:  return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				case ShaderDataType::Mat3:   return 3 * 3;
				case ShaderDataType::Mat4:   return 4 * 4;
			}
		}
	private:
		uint32_t SizeOfShaderDataType(ShaderDataType type) {
			switch (type) {
			case ShaderDataType::Bool:   return 1;
			case ShaderDataType::Int:    return 4;
			case ShaderDataType::Int2:   return 4 * 2;
			case ShaderDataType::Int3:   return 4 * 3;
			case ShaderDataType::Int4:   return 4 * 4;
			case ShaderDataType::Float:  return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Mat3:   return 4 * 3 * 3;
			case ShaderDataType::Mat4:   return 4 * 4 * 4;
			}

			ORIGIN_ASSERT(false, "Unknow ShaderDataType!");
			return 0;
		}
	};

	class ORIGIN_API BufferLayout {
	public:

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements){
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const{ return m_Elements; }

		inline uint32_t GetStride() const { return m_stride; }


		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	private:
		void CalculateOffsetAndStride() {
			uint32_t offset = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_stride = 0;
	};

	class ORIGIN_API VertexBuffer {
	public:
		virtual ~VertexBuffer() {}


		static AssetRef<VertexBuffer> Create();
		static AssetRef<VertexBuffer> Create(float* data, uint32_t size);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void SetData(float* data, uint32_t size) = 0;
	};


	class ORIGIN_API IndexBuffer {
	public:
		virtual ~IndexBuffer(){}

		static AssetRef<IndexBuffer> Create();
		static AssetRef<IndexBuffer> Create(uint32_t* data, uint32_t size);


		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;


		virtual void SetData(uint32_t* data, uint32_t size) = 0;
	};
}