/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "Constant.H"
#include "Scale.H"

#include "fieldTypes.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeFunction1Meshs(Type)                                                   \
    makeFunction1Mesh(Type);                                                       \
    makeFunction1MeshType(Constant, Type);                                         \
    makeFunction1MeshType(Scale, Type);

namespace Foam
{
    makeFunction1Mesh(label);
    makeFunction1MeshType(Constant, label);

    makeFunction1Meshs(scalar);
    makeFunction1Meshs(vector);
    makeFunction1Meshs(sphericalTensor);
    makeFunction1Meshs(symmTensor);
    makeFunction1Meshs(tensor);
}


template<>
Foam::tmp<Foam::Field<Foam::label>>
Foam::Function1MeshTypes::Constant<Foam::label>::integrate
(
    const scalarField& x1,
    const scalarField& x2
) const
{
    NotImplemented;
    return tmp<Field<label>>(new Field<label>(x1.size()));
}


// ************************************************************************* //
