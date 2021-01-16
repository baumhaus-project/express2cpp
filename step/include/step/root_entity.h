#pragma once

#include <iosfwd>
#include <memory>
#include <vector>

namespace step {

struct write_context;

struct root_entity {
  root_entity() = default;
  root_entity(root_entity const&) = delete;
  root_entity(root_entity&&) = delete;
  root_entity& operator=(root_entity const&) = delete;
  root_entity& operator=(root_entity&&) = delete;
  virtual ~root_entity() = default;
  virtual void resolve(std::vector<root_entity*> const&) = 0;
  virtual void write(write_context const&, std::ostream&,
                     bool write_type_name) const = 0;
  friend void write(write_context const& ctx, std::ostream& out,
                    root_entity const& e) {
    e.write(ctx, out, true);
  }
  std::size_t line_idx_{0U};
};

using entity_ptr = std::unique_ptr<root_entity>;

}  // namespace step