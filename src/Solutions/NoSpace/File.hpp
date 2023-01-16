#ifndef SOLLUTIONS_NOSPACE_NOSPACE_FILE_HPP
#define SOLLUTIONS_NOSPACE_NOSPACE_FILE_HPP

#include <memory>

namespace Solutions::NoSpace {

template<typename SizeType> struct Directory;

template<typename SizeType> struct File
{
	File(std::string name, size_t size, const std::shared_ptr<Directory<SizeType>>& parent)
	  : m_name{std::move(name)}, m_size(size), m_parent(parent)
	{
	}

	[[nodiscard]] auto
	getSize() const -> SizeType
	{
	    return m_size;
	}

	auto
	getName() const -> std::string
	{
	    return m_name;
	}

	auto
	getParent() const -> std::shared_ptr<Directory<SizeType>>
	{
	    return m_parent.lock();
	}

    private:

	std::weak_ptr<Directory<SizeType>> m_parent;
	const std::string m_name;
	const SizeType m_size;
};

template struct File<size_t>;

} // namespace Solutions::NoSpace
#endif