//
// Created by Chingkai Chou on 5/25/18.
//

#ifndef ARTPDE_POSITION_VECTOR_HPP
#define ARTPDE_POSITION_VECTOR_HPP

#include <iostream>
#include <array>
#include <memory>
#include <algorithm>

namespace art_pde {
    namespace PositionVector{

        // -------- PointData <Start> -----------
        template <size_t Dimension>
        class PointData{
        public:
            typedef std::array<double,Dimension> ArrayType;
            typedef std::shared_ptr<ArrayType> PtrArrayType;

            PointData<Dimension>& operator=(const PointData<Dimension>& other);

            template <size_t Dimension_>
            friend std::ostream &operator<<(std::ostream &os, const PointData<Dimension_> &point_data);

            void addDataByList(const std::initializer_list<double> &v);

        protected:
            PointData(){ this->newData(); }
            void newData();
            PtrArrayType data{nullptr};
        };
        #include "./src/position_vector_pointdata_impl.cpp"
        // -------- PointData <End> -----------

        // -------- CartesianAPI <Start> -----------
        template <size_t Dimension, bool Authority> class CartesianAPI;
        #include "./src/position_vector_cartesian_impl.cpp"
        // -------- CartesianAPI <End> -----------

        // -------- Real apply class <Start> -----------
        template <size_t Dimension>
        class ViewPositionVector:
                public CartesianAPI<Dimension, false>{
        public:
            ViewPositionVector(): PointData<Dimension>(){}
        };

        template <size_t Dimension>
        class ComputePositionVector:
                public CartesianAPI<Dimension, true>{
        public:
            ComputePositionVector(): PointData<Dimension>(){}

            ComputePositionVector<Dimension>& operator=(const ViewPositionVector<Dimension>& other)
            {
                PointData<Dimension>::operator=(other);
                return *this;
            }
        };
        // -------- Real apply class <End> -----------

        template <size_t Dimension>
        class PositionVector{
        public:
            static std::shared_ptr<ViewPositionVector<Dimension>> createViewPoint(){
                std::shared_ptr<ViewPositionVector<Dimension>> re_ptr;
                re_ptr = std::make_shared<ViewPositionVector<Dimension>>();
                return re_ptr;
            }
            static std::shared_ptr<ViewPositionVector<Dimension>> createViewPoint(std::initializer_list<double> input_list){
                std::shared_ptr<ViewPositionVector<Dimension>> re_ptr;
                re_ptr = std::make_shared<ViewPositionVector<Dimension>>();
                re_ptr->addDataByList(input_list);
                return re_ptr;
            }

            static std::shared_ptr<ComputePositionVector<Dimension>> createComputePoint(){
                std::shared_ptr<ComputePositionVector<Dimension>> re_ptr;
                re_ptr = std::make_shared<ComputePositionVector<Dimension>>();
                return re_ptr;
            }
            static std::shared_ptr<ComputePositionVector<Dimension>> createComputePoint(std::initializer_list<double> input_list){
                std::shared_ptr<ComputePositionVector<Dimension>> re_ptr;
                re_ptr = std::make_shared<ComputePositionVector<Dimension>>();
                re_ptr->addDataByList(input_list);
                return re_ptr;
            }

        private:
            PositionVector() {}
        };


    }
}




#endif //ARTPDE_POSITION_VECTOR_HPP
