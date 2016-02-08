#ifndef RADIUMENGINE_SYSTEM_HPP
#define RADIUMENGINE_SYSTEM_HPP

#include <Engine/RaEngine.hpp>

#include <map>
#include <memory>

#include <Core/Utils/Any.hpp>
#include <Core/Index/Index.hpp>
#include <Core/Event/KeyEvent.hpp>
#include <Core/Event/MouseEvent.hpp>

#include <Engine/Entity/Component.hpp>

namespace Ra
{
    namespace Core
    {
        class TaskQueue;
    }
}

namespace Ra
{
    namespace Engine
    {
        struct FrameInfo;
        class Component;
        class Entity;
    }

    namespace Asset
    {
        class FileData;
    }
}

namespace Ra
{
    namespace Engine
    {

        class RA_ENGINE_API System
        {
        public:
            System();
            virtual ~System();

            /**
             * @brief Pure virtual method to be overridden by any system.
             * A very basic version of this method could be to iterate on components
             * and just call Component::udate() method on them.
             * This update depends on time (e.g. physics system).
             *
             * @param dt Time elapsed since last call.
             */
            virtual void generateTasks( Core::TaskQueue* taskQueue, const Engine::FrameInfo& frameInfo ) = 0;


            /// Registers a component belonging to an entity, making it active within the system.
            void registerComponent( const Entity* entity, Component* component );


            /// Unregisters a component. The system will not update it.
            void unregisterComponent(const Entity* entity, Component* component);

            /// Removes all components belonging to a given entity.
            void unregisterAllComponents( const Entity* entity );



            /**
             * Factory method for component creation from file data.
             * Given a given file and the corresponding entity, the system will create the
             * corresponding components ,add them to the entity.
             */
            virtual void handleAssetLoading( Entity* entity, const Asset::FileData* data) {}



        protected:
            std::vector<std::pair< const Entity*, Component*> > m_components;
        };

    } // namespace Engine
} // namespace Ra

#endif // RADIUMENGINE_SYSTEM_HPP
