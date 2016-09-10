local behavior = {}

function behavior.init(self)
    self.x = 0
    self.y = 0
    
    self.empty = api.get_component_of(self.entity_id, ComponentType.physics)
end

function behavior.tick(self, dt)
    self.x = self.x + 1
    self.y = self.y + 1
    
    api.set_physics_position(self.empty, self.x, self.y)
end

return behavior