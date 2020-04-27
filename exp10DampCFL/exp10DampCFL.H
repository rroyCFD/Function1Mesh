/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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

Class
    Foam::Function1MeshTypes::exp10DampCFL

Description
    exp10 damp function starting from 0 and increasing exp10DampCFLly to 1 from
    \c start over the \c duration and remaining at 1 thereafter.

See also
    Foam::Function1MeshTypes::damp

SourceFiles
    exp10DampCFL.C

\*---------------------------------------------------------------------------*/

#ifndef exp10DampCFL_H
#define exp10DampCFL_H

#include "damp.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace Function1MeshTypes
{

/*---------------------------------------------------------------------------*\
                           Class exp10DampCFL Declaration
\*---------------------------------------------------------------------------*/

class exp10DampCFL
:
    public damp
{
    // Private data
        //- Mesh pointer
        const fvMesh& mesh_;

        // CFL number dictionary
        const dictionary& CFLdict_;

    // Private Member Functions

        //- Disallow default bitwise assignment
        void operator=(const exp10DampCFL&);


public:

    // Runtime type information
    TypeName("exp10DampCFL");


    // Constructors

        //- Construct from entry name and dictionary
        exp10DampCFL
        (
            const word& entryName,
            const dictionary& dict,
            const fvMesh& mesh
        );


    //- Destructor
    virtual ~exp10DampCFL();


    // Member Functions

        //- Return value for time t
        virtual inline scalar value(const scalar t) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Function1MeshTypes
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "exp10DampCFLI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
